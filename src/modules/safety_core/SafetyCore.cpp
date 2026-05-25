#include "modules/safety_core/SafetyCore.h"

namespace vrp {

SensorGroundTruth SafetyCore::truth_from_fdm(const FDMState &fdm) const {
  SensorGroundTruth truth{};
  truth.ax = fdm.ax;
  truth.ay = fdm.ay;
  truth.az = fdm.az;
  truth.gx = fdm.gx;
  truth.gy = fdm.gy;
  truth.gz = fdm.gz;
  truth.yaw_deg = fdm.yaw_deg;
  return truth;
}

bool SafetyCore::init(const std::string &vehicle, VRPParamStore &params) {
  vehicle_ = vehicle;
  tick_ = 0;
  fence_breach_ = false;
  mission_upload_expected_ = 0;
  params.set("system.auto_arm_sitl", 1.0);

  sensors_.init();
  ins_.init();
  ahrs_.init();
  ekf3_.init();
  batt_.init(10.5);
  arming_.init(params.get("system.auto_arm_sitl", 1.0) > 0.5);
  logger_.init();
  fence_.init(0.0, 0.0, 50.0, -20.0, 2.0);
  smart_rtl_.init(64, 0.5);
  failsafe_.init(params);
  avoidance_.init();
  stats_.init();
  open_drone_id_.init();

  std::vector<Waypoint> wps;
  if (vehicle == "boat") {
    wps.push_back(Waypoint{5.0, 0.0, 0.0});
    wps.push_back(Waypoint{10.0, 2.0, 0.0});
  } else {
    wps.push_back(Waypoint{0.0, 0.0, -5.0});
    wps.push_back(Waypoint{2.0, 1.0, -6.0});
  }
  mission_.init(wps, 2.0);
  mode_ = "Stabilize";
  logger_.write(0, "boot");
  return true;
}

void SafetyCore::configure_adsb_test(double intruder_x_m) { sensors_.set_adsb_intruder_x(intruder_x_m); }

void SafetyCore::apply_mavlink_action(const MavlinkRxAction &action) {
  if (action.disarm) {
    arming_.request_disarm();
    logger_.write(tick_, "mavlink_disarm");
  }
  if (action.arm) {
    arming_.request_arm();
    logger_.write(tick_, "mavlink_arm");
  }
  if (action.mission_clear) {
    mission_.clear();
    mission_upload_expected_ = action.mission_expected;
  }
  if (action.mission_item) {
    mission_.add_item_int(action.mission_lat_e7, action.mission_lon_e7, action.mission_alt_m);
    if (mission_upload_expected_ > 0 && mission_.waypoint_count() >= mission_upload_expected_) {
      mission_.finalize_upload();
      mission_upload_ack_pending_ = true;
      logger_.write(tick_, "mission_upload");
    }
  }
}

void SafetyCore::note_gcs_link(uint64_t tick) { failsafe_.note_gcs_link(tick); }

void SafetyCore::enter_rtl(const std::string &reason) {
  mode_ = "RTL";
  rtl_active_ = true;
  smart_rtl_state_ = smart_rtl_.activate();
  const std::string log_msg = "rtl_" + reason;
  logger_.write(tick_, log_msg.c_str());
}

void SafetyCore::update(double dt_s, uint64_t time_ms, const FDMState &fdm, UORB &uorb) {
  ++tick_;
  const uint64_t time_us = time_ms * 1000U;

  const SensorSnapshot snap = sensors_.update(fdm, time_us, tick_);
  gps_ = snap.gps;
  uorb.publish("sensor/gps", format_gps(snap.gps));
  uorb.publish("sensor/baro", format_baro(snap.baro));
  uorb.publish("sensor/compass", format_compass(snap.compass));
  uorb.publish("sensor/airspeed", format_airspeed(snap.airspeed));
  uorb.publish("sensor/optical_flow", format_optical_flow(snap.optical_flow));

  const ImuSample imu = ins_.update(truth_from_fdm(fdm), time_us, dt_s);
  uorb.publish("sensor/imu", format_imu(imu));

  attitude_ = ahrs_.update(imu, dt_s);
  uorb.publish("vehicle/attitude", format_attitude(attitude_));

  position_ = ekf3_.update(snap.measurement, dt_s);
  uorb.publish("estimator/local_position", format_local_position(position_));

  battery_ = batt_.update(tick_);
  uorb.publish("sensor/battery", format_battery(battery_));

  std::string fence_detail;
  const FenceStatus fence_status = fence_.check(position_, fence_detail);
  fence_breach_ = fence_status == FenceStatus::Breach;
  uorb.publish("fence/status", fence_detail);

  const bool was_armed = arming_.is_armed();
  arming_.update(tick_, imu, battery_, position_);
  if (!was_armed && arming_.is_armed()) {
    logger_.write(time_ms, "armed");
  }
  if (fence_breach_) {
    logger_.write(time_ms, "fence_breach");
  }
  uorb.publish("vehicle/arming", arming_.status_text());
  uorb.publish("logger/status", logger_.summary());

  const std::string mission_state = mission_.update(position_);
  uorb.publish("mission/state", mission_state);

  if (arming_.is_armed()) {
    smart_rtl_.update(position_, true);
  } else {
    smart_rtl_.clear();
    rtl_active_ = false;
  }

  failsafe_.update(tick_, battery_, arming_.is_armed());
  uorb.publish("failsafe/status", failsafe_.status());
  uorb.publish("smart_rtl/status", smart_rtl_.status());

  if (rtl_active_ && arming_.is_armed()) {
    smart_rtl_state_ = smart_rtl_.update_rtl(position_);
    uorb.publish("smart_rtl/nav", format_smart_rtl(smart_rtl_state_));
  }

  if (!arming_.is_armed()) {
    mode_ = "Disarmed";
    rtl_active_ = false;
  } else if (failsafe_.should_rtl()) {
    if (!rtl_active_) {
      enter_rtl(failsafe_.reason());
    }
  } else if (fence_breach_) {
    if (!rtl_active_) {
      enter_rtl("fence");
    }
  } else if (mission_state.find("complete") != std::string::npos) {
    if (!rtl_active_) {
      enter_rtl("mission");
    }
  } else {
    rtl_active_ = false;
    if (vehicle_ == "boat") {
      mode_ = "Auto";
    } else {
      mode_ = "Loiter";
    }
  }

  avoidance_out_ = avoidance_.update(sensors_.adsb(), sensors_.proximity());
  uorb.publish("avoidance/status", format_avoidance(avoidance_out_));
  stats_.update(tick_, arming_.is_armed(), position_, dt_s);
  uorb.publish("stats/summary", stats_.summary());
  open_drone_line_ = open_drone_id_.broadcast(gps_, arming_.is_armed(), mode_, time_ms);
  uorb.publish("open_drone_id/status", open_drone_line_);
}

bool SafetyCore::is_armed() const { return arming_.is_armed(); }

bool SafetyCore::fence_breached() const { return fence_breach_; }

std::string SafetyCore::flight_mode() const { return mode_; }

const Attitude &SafetyCore::attitude() const { return attitude_; }

const LocalPosition &SafetyCore::position() const { return position_; }

const BatteryStatus &SafetyCore::battery() const { return battery_; }

const GpsSample &SafetyCore::gps() const { return gps_; }

std::string SafetyCore::logger_summary() const { return logger_.summary(); }

std::string SafetyCore::sensors_summary() const {
  return format_gps(gps_) + " | " + format_baro(sensors_.baro()) + " | " + format_compass(sensors_.compass()) +
         " | " + format_airspeed(sensors_.airspeed()) + " | " + format_optical_flow(sensors_.optical_flow()) +
         " | " + format_rangefinder(sensors_.rangefinder()) + " | " + format_proximity(sensors_.proximity()) +
         " | " + format_adsb(sensors_.adsb());
}

bool SafetyCore::mission_active() const { return mission_.has_active_target(); }

bool SafetyCore::mission_complete() const { return mission_.complete(); }

size_t SafetyCore::mission_index() const { return mission_.current_index(); }

size_t SafetyCore::mission_waypoint_count() const { return mission_.waypoint_count(); }

Waypoint SafetyCore::mission_prev_target() const { return mission_.prev_target(); }

bool SafetyCore::mission_get_item_int(uint16_t seq, int32_t &lat_e7, int32_t &lon_e7, float &alt_m) const {
  return mission_.get_item_int(seq, lat_e7, lon_e7, alt_m);
}

bool SafetyCore::mission_upload_ack_pending() const { return mission_upload_ack_pending_; }

void SafetyCore::clear_mission_upload_ack() { mission_upload_ack_pending_ = false; }

MissionTxView SafetyCore::build_mission_tx(const MavlinkRxAction &rx) const {
  MissionTxView view{};
  view.waypoint_count = mission_.waypoint_count();
  view.send_upload_ack = mission_upload_ack_pending_;
  const RangeFinderSample &rng = sensors_.rangefinder();
  if (rng.valid) {
    view.send_distance_sensor = true;
    view.distance_m = static_cast<float>(rng.distance_m);
  }
  if (rx.mission_request_list) {
    view.send_count = true;
  }
  if (rx.mission_request_item) {
    view.send_item = true;
    view.item_seq = rx.mission_request_seq;
    mission_.get_item_int(rx.mission_request_seq, view.item_lat_e7, view.item_lon_e7, view.item_alt_m);
  }
  return view;
}

int SafetyCore::consume_mission_item_reached() { return mission_.consume_reached_index(); }

const RangeFinderSample &SafetyCore::rangefinder() const { return sensors_.rangefinder(); }

const ProximitySample &SafetyCore::proximity() const { return sensors_.proximity(); }

const AdsbVehicle &SafetyCore::adsb() const { return sensors_.adsb(); }

const AirspeedSample &SafetyCore::airspeed() const { return sensors_.airspeed(); }

const OpticalFlowSample &SafetyCore::optical_flow() const { return sensors_.optical_flow(); }

Waypoint SafetyCore::mission_target() const { return mission_.active_target(); }

Waypoint SafetyCore::nav_target() const {
  if (rtl_active_ && smart_rtl_state_.active) {
    return smart_rtl_state_.target;
  }
  return mission_.active_target();
}

bool SafetyCore::rtl_nav_active() const { return rtl_active_ && smart_rtl_state_.active; }

const std::string &SafetyCore::mission_status() const { return mission_.last_status(); }

std::string SafetyCore::failsafe_summary() const { return failsafe_.status(); }

std::string SafetyCore::smart_rtl_summary() const {
  if (rtl_active_) {
    return format_smart_rtl(smart_rtl_state_);
  }
  return smart_rtl_.status();
}

std::string SafetyCore::avoidance_summary() const { return format_avoidance(avoidance_out_); }

std::string SafetyCore::stats_summary() const { return stats_.summary(); }

std::string SafetyCore::open_drone_id_line() const { return open_drone_line_; }

} // namespace vrp
