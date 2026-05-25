#include "modules/copter_core/CopterCore.h"

#include "libraries/VRP_Math/VRP_Math.h"

#include <cmath>

namespace vrp {

bool CopterCore::init(VRPParamStore &params) {
  max_tilt_rad_ = VRP_Math::deg_to_rad(params.get("quad.max_tilt_deg", 35.0));
  loiter_radius_m_ = params.get("nav.loiter_radius", 5.0);
  input_mgr_.init();
  precland_.init();
  autotune_lib_.init();
  custom_ctl_.init();
  sprayer_.init();
  ac_pid_.init();
  landing_.init();
  inertial_nav_.init();
  surface_.init();
  follow_.init();
  rally_.init();
  takeoff_.init(params.get("takeoff.min_throttle", 0.55), params.get("takeoff.min_climb_m_s", 0.3));
  terrain_.init();
  motor_spool_ = 0.0F;
  request_disarm_ = false;
  return true;
}

double CopterCore::terrain_target_z(double target_z, const CopterAuxInputs &aux) const {
  if (!aux.terrain_valid) {
    return target_z + aux.baro_ground_corr;
  }
  const double terrain_rel = aux.terrain_amsl_m - 120.0;
  return VRP_Math::clamp(target_z + terrain_rel * 0.02, target_z - 5.0, target_z + 2.0);
}

float CopterCore::autotune_scale() const {
  if (!autotune_state_.active) {
    return 1.0F;
  }
  return 1.0F + static_cast<float>(autotune_state_.pct) * 0.01F;
}

void CopterCore::apply_rc_stabilize(VehicleSetpoints &sp, const RcChannels &rc, double max_tilt_rad) const {
  sp.attitude.roll_rad = rc.roll * max_tilt_rad;
  sp.attitude.pitch_rad = rc.pitch * max_tilt_rad;
  sp.attitude.yaw_rate_rad_s = rc.yaw * 1.5;
  sp.attitude.thrust_base = static_cast<float>(VRP_Math::clamp(0.5 + rc.throttle * 0.45, 0.0, 0.95));
}

void CopterCore::apply_flow_loiter(VehicleSetpoints &sp, const OpticalFlowSample &flow, double max_tilt_rad) const {
  if (!flow.valid || flow.quality < 50) {
    return;
  }
  const double gain = 0.15;
  sp.attitude.roll_rad = VRP_Math::clamp(sp.attitude.roll_rad - flow.flow_x_rad_s * gain, -max_tilt_rad, max_tilt_rad);
  sp.attitude.pitch_rad = VRP_Math::clamp(sp.attitude.pitch_rad - flow.flow_y_rad_s * gain, -max_tilt_rad, max_tilt_rad);
}

void CopterCore::apply_custom_overlay(VehicleSetpoints &sp, const CustomControlState &custom,
                                      double max_tilt_rad) const {
  if (!custom.active) {
    return;
  }
  sp.attitude.roll_rad = VRP_Math::clamp(sp.attitude.roll_rad + custom.roll * max_tilt_rad * 0.25, -max_tilt_rad,
                                         max_tilt_rad);
  sp.attitude.pitch_rad = VRP_Math::clamp(sp.attitude.pitch_rad + custom.pitch * max_tilt_rad * 0.25, -max_tilt_rad,
                                          max_tilt_rad);
}

void CopterCore::apply_nav_attitude(VehicleSetpoints &sp, const WpNavOutput &nav, double max_tilt_rad,
                                    double target_z, const LocalPosition &pos, const CopterAuxInputs &aux) const {
  const double lean = VRP_Math::clamp(nav.target_speed_m_s / 6.0 * max_tilt_rad, 0.0, max_tilt_rad);
  sp.attitude.roll_rad = std::sin(nav.bearing_rad) * lean;
  sp.attitude.pitch_rad = std::cos(nav.bearing_rad) * lean;
  sp.attitude.yaw_rate_rad_s = nav.turn_rate_rad_s;
  sp.attitude.heading_hold = true;
  sp.attitude.yaw_target_rad = nav.bearing_rad;
  if (inertial_state_.valid) {
    sp.attitude.roll_rad =
        VRP_Math::clamp(sp.attitude.roll_rad - inertial_state_.vx_m_s * 0.05, -max_tilt_rad, max_tilt_rad);
    sp.attitude.pitch_rad =
        VRP_Math::clamp(sp.attitude.pitch_rad - inertial_state_.vy_m_s * 0.05, -max_tilt_rad, max_tilt_rad);
  }
  const double tz = terrain_target_z(target_z, aux);
  double alt_adj = nav.alt_error_m * 0.05;
  if (surface_state_.valid) {
    alt_adj += VRP_Math::clamp(2.0 - surface_state_.agl_m, -0.5, 0.5) * 0.08;
  }
  sp.attitude.thrust_base =
      static_cast<float>(VRP_Math::clamp(0.55 + 0.12 * (tz - pos.z) + alt_adj, 0.35, 0.9));
  sp.nav_active = true;
  sp.nav_bearing_rad = nav.bearing_rad;
  sp.nav_speed_m_s = nav.target_speed_m_s;
  if (aux.flow != nullptr && (aux.flow_fusion || aux.flow->valid)) {
    apply_flow_loiter(sp, *aux.flow, max_tilt_rad);
  }
}

void CopterCore::apply_avoidance(VehicleSetpoints &sp, const AvoidanceOutput &avoidance, double max_tilt_rad) const {
  if (!avoidance.active) {
    return;
  }
  const double bias = VRP_Math::clamp(avoidance.speed_m_s / 4.0 * max_tilt_rad * 0.35, 0.05, max_tilt_rad * 0.4);
  sp.attitude.roll_rad += std::sin(avoidance.bearing_rad) * bias;
  sp.attitude.pitch_rad += std::cos(avoidance.bearing_rad) * bias;
}

VehicleSetpoints CopterCore::build_setpoints(const std::string &mode, const LocalPosition &pos,
                                             const WpNavOutput &nav, const RcChannels &rc,
                                             const AvoidanceOutput &avoidance, const RangeFinderSample &rng,
                                             LandingSetpoint &landing_sp, double target_z, double dt_s,
                                             const CopterAuxInputs &aux) {
  VehicleSetpoints sp{};
  sp.attitude.thrust_base = 0.55F;
  request_disarm_ = false;
  const double tz = terrain_target_z(target_z, aux);
  (void)input_mgr_.update(rc, mode != "Disarmed");
  inertial_state_ = inertial_nav_.update(pos, mode != "Disarmed");
  surface_state_ = surface_.update(rng, sp.attitude.pitch_rad);
  follow_state_ = follow_.update(mode, aux.follow_target_x, aux.follow_target_y, pos.x, pos.y);
  sprayer_state_ = sprayer_.update(mode == "Auto", rc.aux2);
  custom_state_ = custom_ctl_.update(mode != "Disarmed", rc.roll, rc.pitch);
  ac_pid_state_ = ac_pid_.update(mode != "Disarmed", static_cast<float>(nav.cross_track_m));
  const double agl = rng.valid ? rng.distance_m : -pos.z;
  takeoff_state_ = takeoff_.update(mode != "Disarmed", rc.throttle, pos.vz, agl, dt_s);

  const bool want_thrust = mode != "Disarmed" && mode != "Land";
  motor_spool_ = want_thrust ? VRP_Math::clamp(motor_spool_ + static_cast<float>(dt_s * 3.0), 0.0F, 1.0F)
                             : VRP_Math::clamp(motor_spool_ - static_cast<float>(dt_s * 5.0), 0.0F, 1.0F);

  if (mode == "Land") {
    landing_sp = landing_.update(pos, rng, dt_s);
    sp.attitude.thrust_base = landing_sp.complete
                                  ? 0.0F
                                  : static_cast<float>(VRP_Math::clamp(
                                        (0.45 + 0.15 * (landing_sp.target_z_m - pos.z)) * motor_spool_, 0.0, 0.75));
    prec_land_ = precland_.update(rng, true, mode);
    if (prec_land_.target_ok) {
      sp.attitude.roll_rad *= 0.3;
      sp.attitude.pitch_rad *= 0.3;
    }
    if (landing_sp.request_disarm) {
      request_disarm_ = true;
    }
    apply_avoidance(sp, avoidance, max_tilt_rad_);
    return sp;
  }

  prec_land_ = precland_.update(rng, mode != "Disarmed", mode);
  autotune_state_ = autotune_lib_.update(mode != "Disarmed", rc.aux1, static_cast<uint64_t>(dt_s * 1000.0));

  if (mode == "Acro") {
    sp.attitude.acro_rate = true;
    sp.attitude.roll_rad = rc.roll * 4.0;
    sp.attitude.pitch_rad = rc.pitch * 4.0;
    sp.attitude.yaw_rate_rad_s = rc.yaw * 3.0;
    sp.attitude.thrust_base = static_cast<float>(VRP_Math::clamp(0.5 + rc.throttle * 0.45, 0.0, 0.95));
  } else if (mode == "Stabilize" || mode == "Sport") {
    const RcChannels rc_in = input_mgr_.apply_stabilize(rc, max_tilt_rad_);
    apply_rc_stabilize(sp, rc_in, mode == "Sport" ? max_tilt_rad_ * 1.2 : max_tilt_rad_);
  } else if (mode == "Brake") {
    sp.attitude.roll_rad = VRP_Math::clamp(-pos.vx * 0.25, -max_tilt_rad_, max_tilt_rad_);
    sp.attitude.pitch_rad = VRP_Math::clamp(-pos.vy * 0.25, -max_tilt_rad_, max_tilt_rad_);
    sp.attitude.heading_hold = true;
    sp.attitude.yaw_target_rad = pos.valid ? std::atan2(pos.vy, pos.vx) : 0.0;
    sp.attitude.thrust_base = static_cast<float>(VRP_Math::clamp(0.55 + 0.12 * (tz - pos.z), 0.4, 0.75));
  } else if (mode == "PosHold" || mode == "AltHold" || mode == "Loiter" || mode == "Guided" || mode == "FlowHold") {
    if (mode != "PosHold" && mode != "FlowHold") {
      apply_rc_stabilize(sp, rc, max_tilt_rad_ * 0.35);
    }
    if (nav.valid || mode == "PosHold" || mode == "FlowHold") {
      WpNavOutput hold_nav = nav.valid ? nav : WpNavOutput{};
      if (!hold_nav.valid) {
        hold_nav.valid = true;
        hold_nav.bearing_rad = 0.0;
        hold_nav.target_speed_m_s = 0.0;
      }
      apply_nav_attitude(sp, hold_nav, max_tilt_rad_, tz, pos, aux);
    } else {
      sp.attitude.thrust_base =
          static_cast<float>(VRP_Math::clamp(0.55 + 0.15 * (tz - pos.z), 0.35, 0.85));
      sp.attitude.heading_hold = true;
    }
    if (mode == "Guided" && aux.follow_enabled && follow_state_.active) {
      const double brg = VRP_Math::deg_to_rad(follow_state_.bearing_deg);
      sp.attitude.roll_rad = std::sin(brg) * max_tilt_rad_ * 0.4;
      sp.attitude.pitch_rad = std::cos(brg) * max_tilt_rad_ * 0.4;
    }
    if (mode == "FlowHold" && aux.flow != nullptr) {
      apply_flow_loiter(sp, *aux.flow, max_tilt_rad_);
    }
  } else if (mode == "Follow") {
    if (follow_state_.active) {
      const double brg = VRP_Math::deg_to_rad(follow_state_.bearing_deg);
      sp.attitude.roll_rad = std::sin(brg) * max_tilt_rad_ * 0.55;
      sp.attitude.pitch_rad = std::cos(brg) * max_tilt_rad_ * 0.55;
      sp.attitude.heading_hold = true;
      sp.attitude.yaw_target_rad = brg;
    }
    sp.attitude.thrust_base = static_cast<float>(VRP_Math::clamp(0.55 + 0.12 * (tz - pos.z), 0.4, 0.85));
  } else if (mode == "Auto" || mode == "RTL" || mode == "SmartRTL") {
    WpNavOutput use_nav = nav;
    if (mode == "SmartRTL" && aux.smart_rtl != nullptr && aux.smart_rtl->active) {
      use_nav.valid = true;
      use_nav.bearing_rad = std::atan2(aux.smart_rtl->target.y - pos.y, aux.smart_rtl->target.x - pos.x);
      use_nav.target_speed_m_s = 2.5;
      use_nav.distance_m = std::hypot(aux.smart_rtl->target.x - pos.x, aux.smart_rtl->target.y - pos.y);
    }
    if (use_nav.valid) {
      apply_nav_attitude(sp, use_nav, max_tilt_rad_, tz, pos, aux);
    } else if (aux.rally != nullptr && aux.rally->valid && (mode == "RTL" || mode == "SmartRTL")) {
      WpNavOutput rally_nav{};
      rally_nav.valid = true;
      rally_nav.bearing_rad = std::atan2(-pos.y, -pos.x);
      rally_nav.target_speed_m_s = 2.0;
      apply_nav_attitude(sp, rally_nav, max_tilt_rad_, tz, pos, aux);
    } else {
      sp.attitude.thrust_base = 0.5F;
    }
  }

  if (takeoff_state_.check_pass && !takeoff_state_.complete && mode != "Land") {
    sp.attitude.thrust_base = static_cast<float>(VRP_Math::clamp(
        static_cast<double>(sp.attitude.thrust_base) * (takeoff_state_.phase == "climbing" ? 1.0 : 0.85), 0.35, 0.95));
  }

  apply_custom_overlay(sp, custom_state_, max_tilt_rad_);
  if (ac_pid_state_.active) {
    sp.attitude.roll_rad =
        VRP_Math::clamp(sp.attitude.roll_rad + static_cast<double>(ac_pid_state_.output) * 0.08, -max_tilt_rad_,
                        max_tilt_rad_);
  }
  apply_avoidance(sp, avoidance, max_tilt_rad_);
  sp.attitude.roll_rad = VRP_Math::clamp(sp.attitude.roll_rad, -max_tilt_rad_, max_tilt_rad_);
  sp.attitude.pitch_rad = VRP_Math::clamp(sp.attitude.pitch_rad, -max_tilt_rad_, max_tilt_rad_);
  sp.attitude.thrust_base = static_cast<float>(VRP_Math::clamp(static_cast<double>(sp.attitude.thrust_base) * motor_spool_,
                                                                 0.0, 0.95));
  return sp;
}

} // namespace vrp
