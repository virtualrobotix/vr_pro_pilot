#include "modules/vehicle_core/VehicleCore.h"

#include "libraries/VRP_Math/VRP_Math.h"

#include <cmath>

namespace vrp {

bool VehicleCore::init(const std::string &vehicle, VRPParamStore &params) {
  vehicle_ = vehicle;
  target_z_ = params.get("control.target_z", -5.0);
  rc_proto_.init();
  rc_map_.init();
  osd_.init();
  scripting_.init(params.get("script.enable", 1.0) > 0.5);
  landing_.init();
  gear_.init();
  rssi_.init();
  mode_ = vehicle == "vtol" ? "QStabilize" : "Stabilize";
  vtol_phase_ = "MC";
  return true;
}

void VehicleCore::update_vtol_phase(uint64_t tick) {
  if (vehicle_ != "vtol") {
    return;
  }
  if (tick < 3) {
    vtol_phase_ = "MC";
    mode_ = "QStabilize";
  } else if (tick < 5) {
    vtol_phase_ = "TRANSITION";
    mode_ = "Transition";
  } else {
    vtol_phase_ = "FW";
    mode_ = "FW";
  }
}

void VehicleCore::build_setpoints(const LocalPosition &pos, const WpNavOutput &nav, const RangeFinderSample &rng,
                                  double dt_s) {
  setpoints_ = VehicleSetpoints{};
  setpoints_.attitude.roll_rad = 0.0;
  setpoints_.attitude.pitch_rad = 0.0;
  setpoints_.attitude.yaw_rate_rad_s = 0.0;
  setpoints_.attitude.thrust_base = 0.55;

  if (nav.valid) {
    setpoints_.nav_active = true;
    setpoints_.nav_bearing_rad = nav.bearing_rad;
    setpoints_.nav_speed_m_s = nav.target_speed_m_s;
  }

  if (mode_ == "Land" && vehicle_ == "quad") {
    landing_sp_ = landing_.update(pos, rng, dt_s);
    setpoints_.attitude.thrust_base = landing_sp_.throttle;
    setpoints_.hold_position = false;
    target_z_ = landing_sp_.target_z_m;
    setpoints_.attitude.thrust_base =
        landing_sp_.complete ? 0.0F : static_cast<float>(VRP_Math::clamp(0.45 + 0.15 * (target_z_ - pos.z), 0.0, 0.75));
    return;
  }

  if (mode_ == "RTL") {
    setpoints_.hold_position = true;
    setpoints_.attitude.thrust_base = 0.45;
    setpoints_.boat_forward = 0.2F;
    return;
  }

  if (mode_ == "Auto") {
    setpoints_.hold_position = false;
    if (nav.valid) {
      setpoints_.boat_forward =
          static_cast<float>(VRP_Math::clamp(nav.target_speed_m_s / 6.0, 0.25, 0.85));
      setpoints_.boat_turn = static_cast<float>(VRP_Math::clamp(std::sin(nav.bearing_rad) * 0.35, -0.35, 0.35));
      setpoints_.attitude.yaw_rate_rad_s = VRP_Math::clamp(std::sin(nav.bearing_rad) * 0.2, -0.5, 0.5);
      setpoints_.attitude.thrust_base = VRP_Math::clamp(0.5 + 0.05 * nav.distance_m, 0.4, 0.85);
    } else {
      setpoints_.boat_forward = static_cast<float>(VRP_Math::clamp(0.55 + 0.03 * pos.x, 0.3, 0.85));
      setpoints_.boat_turn =
          static_cast<float>(VRP_Math::clamp(static_cast<double>(pos.y) * 0.015, -0.25, 0.25));
      setpoints_.attitude.thrust_base = VRP_Math::clamp(0.55 + 0.05 * pos.x, 0.4, 0.8);
    }
    return;
  }

  if (mode_ == "AltHold" || mode_ == "Loiter" || mode_ == "DepthHold" || mode_ == "Guided") {
    setpoints_.attitude.thrust_base = VRP_Math::clamp(0.55 + 0.15 * (target_z_ - pos.z), 0.35, 0.85);
    setpoints_.subsea_thrust = static_cast<float>(setpoints_.attitude.thrust_base);
  }

  if (mode_ == "FW" && vehicle_ == "vtol") {
    setpoints_.use_tecs = true;
    setpoints_.use_apm = true;
    setpoints_.attitude.pitch_rad = -0.15;
    setpoints_.attitude.thrust_base = 0.65;
  }

  if (mode_ == "Transition" && vehicle_ == "vtol") {
    setpoints_.attitude.pitch_rad = -0.05;
    setpoints_.attitude.thrust_base = 0.6;
  }

  if (mode_ == "Manual" && vehicle_ == "boat") {
    setpoints_.boat_forward = rc_.throttle;
    setpoints_.boat_turn = rc_.yaw;
  }
}

void VehicleCore::apply_mavlink(const MavlinkRxAction &action) {
  if (!action.set_mode) {
    return;
  }
  mavlink_mode_ = mavlink_mode_from_custom(vehicle_, action.custom_mode);
  mavlink_mode_active_ = !mavlink_mode_.empty();
  if (mavlink_mode_ == "Land") {
    landing_.reset();
  }
}

void VehicleCore::update(uint64_t tick, bool armed, const std::string &safety_mode, const LocalPosition &pos,
                         const BatteryStatus &battery, const WpNavOutput &nav, const RangeFinderSample &rng,
                         bool gcs_link, UORB &uorb) {
  tick_ = tick;
  rc_ = rc_proto_.update(tick);
  last_rssi_sample_ = rssi_.update(tick, gcs_link);
  last_rssi_ = format_rssi(last_rssi_sample_);

  if (!armed || safety_mode == "Disarmed") {
    mode_ = "Disarmed";
  } else if (mavlink_mode_active_ && mavlink_mode_ == "Land") {
    mode_ = "Land";
    landing_.reset();
  } else if (safety_mode == "RTL") {
    mode_ = "RTL";
  } else if (mavlink_mode_active_) {
    mode_ = mavlink_mode_;
    if (mode_ == "Land" && vehicle_ == "quad") {
      landing_.reset();
    }
    if (vehicle_ == "vtol") {
      if (mode_ == "FW") {
        vtol_phase_ = "FW";
      } else if (mode_ == "Transition") {
        vtol_phase_ = "TRANSITION";
      } else {
        vtol_phase_ = "MC";
      }
    }
  } else if (vehicle_ == "vtol") {
    update_vtol_phase(tick);
  } else {
    mode_ = rc_map_.mode_from_rc(vehicle_, rc_);
    if (mode_ == "Manual" && vehicle_ == "quad") {
      mode_ = "Loiter";
    }
  }

  script_line_ = scripting_.update(tick, mode_);
  if (!mavlink_mode_active_ && script_line_.find("mode_hint:Auto") != std::string::npos && armed &&
      safety_mode != "RTL") {
    mode_ = "Auto";
  }

  build_setpoints(pos, nav, rng, 0.02);
  gear_.update(armed, mode_ == "Land");

  last_osd_ = osd_.render(mode_, pos, battery, armed);
  uorb.publish("rc/channels", format_rc(rc_));
  uorb.publish("rc/rssi", last_rssi_);
  uorb.publish("vehicle/mode", mode_);
  uorb.publish("landing/status", format_landing(landing_sp_));
  uorb.publish("script/status", script_line_);
  uorb.publish("osd/screen", last_osd_);

  (void)tick_;
}

} // namespace vrp
