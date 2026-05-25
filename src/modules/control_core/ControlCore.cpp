#include "modules/control_core/ControlCore.h"

#include <string>

#include "libraries/VRP_AC_AttitudeControl/VRP_AC_AttitudeControl.h"
#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool ControlCore::init(const std::string &vehicle, VRPParamStore &params) {
  vehicle_ = vehicle;
  target_z_ = params.get("control.target_z", -5.0);
  att_ctrl_.init(params.get("quad.max_tilt_deg", 35.0));
  att_ctrl_.set_hover_throttle(static_cast<float>(params.get("motors.hover_throttle", 0.55)));
  motors_.init(params.get("quad.max_tilt_deg", 35.0));
  apm_ctrl_.init();
  tecs_.init(5.0, 12.0);
  if (is_ar_surface_vehicle(vehicle)) {
    const double max_speed = params.get(vehicle + ".max_speed_mps",
                                        vehicle == "rover" ? 4.0 : (vehicle == "sailboat" ? 4.0 : 6.0));
    ar_att_ctrl_.init(max_speed);
    if (vehicle == "rover") {
      ar_motors_.init(ArFrameClass::Rover, true);
    } else {
      ar_motors_.init(ArFrameClass::Boat, params.get("rover.skid_steer", 1.0) > 0.5);
    }
    if (vehicle == "sailboat") {
      sailboat_.init(max_speed);
      wind_vane_.init();
    }
  }
  quad_out_ = MotorOutputQuad{};
  boat_out_ = BoatActuators{};
  last_ar_motors_ = ArMotorsState{};
  return true;
}

MotorOutputQuad ControlCore::update_quad(bool armed, bool fence_breach, const Attitude &attitude,
                                         const LocalPosition &pos, const VehicleSetpoints &sp, double dt_s,
                                         UORB &uorb, float autotune_scale, float motor_spool) {
  if (!armed || fence_breach) {
    quad_out_ = MotorOutputQuad{};
    uorb.publish("control/attitude", "ATT_CTRL disarmed");
    uorb.publish("actuators/quad", format_motors_quad(quad_out_));
    return quad_out_;
  }

  att_ctrl_.apply_autotune_scale(autotune_scale);
  AttitudeSetpoint asp = sp.attitude;
  if (sp.nav_active && pos.valid) {
    WpNavOutput nav{};
    nav.valid = true;
    nav.bearing_rad = sp.nav_bearing_rad;
    nav.target_speed_m_s = sp.nav_speed_m_s;
    nav.turn_rate_rad_s = sp.desired_turn_rate_rad_s;
    const auto pos_sp = att_ctrl_.update_pos(pos, nav, target_z_, 0.61, true);
    asp.roll_rad = pos_sp.roll_rad;
    asp.pitch_rad = pos_sp.pitch_rad;
    asp.yaw_rate_rad_s = pos_sp.yaw_rate_rad_s;
    asp.thrust_base = pos_sp.thrust_base;
    uorb.publish("control/pos", format_pos_control(pos_sp));
  } else if (asp.thrust_base <= 0.0) {
    asp.thrust_base = VRP_Math::clamp(0.55 + 0.15 * (target_z_ - pos.z), 0.35, 0.85);
  }

  const ControlTorque torque = att_ctrl_.update(attitude, asp, dt_s);
  quad_out_ = motors_.mix_quad(static_cast<float>(asp.thrust_base), torque, motor_spool, 0.18F);

  uorb.publish("control/attitude", "ATT_CTRL active roll=" + std::to_string(torque.roll) +
                                        " pitch=" + std::to_string(torque.pitch));
  uorb.publish("actuators/quad", format_motors_quad(quad_out_));
  return quad_out_;
}

MotorOutputQuad ControlCore::update_vtol(bool armed, bool fence_breach, const Attitude &attitude,
                                         const LocalPosition &pos, const VehicleSetpoints &sp, double airspeed_m_s,
                                         double dt_s, UORB &uorb) {
  if (!armed || fence_breach) {
    quad_out_ = MotorOutputQuad{};
    uorb.publish("control/tecs", "TECS idle");
    uorb.publish("vtol/actuators", format_motors_quad(quad_out_));
    return quad_out_;
  }

  AttitudeSetpoint asp = sp.attitude;
  if (sp.use_tecs) {
    const double tas = airspeed_m_s > 0.1 ? airspeed_m_s : std::abs(pos.vx);
    const TecsOutput tecs = tecs_.update(-pos.z, tas, dt_s);
    asp.pitch_rad = tecs.pitch_rad;
    asp.thrust_base = tecs.throttle;
    uorb.publish("control/tecs", "TECS pitch=" + std::to_string(tecs.pitch_rad) +
                                     " thr=" + std::to_string(tecs.throttle) +
                                     " airspd=" + std::to_string(tas));
    if (sp.use_apm && sp.nav_active) {
      FwNavSetpoint nav{};
      nav.bearing_rad = sp.nav_bearing_rad;
      nav.speed_m_s = sp.nav_speed_m_s;
      nav.valid = true;
      FwControlSetpoint tecs_sp{};
      tecs_sp.pitch_rad = tecs.pitch_rad;
      const FwControlSetpoint fw = apm_ctrl_.update(attitude, nav, tecs_sp, dt_s);
      asp.roll_rad = fw.roll_rad;
      asp.pitch_rad = fw.pitch_rad;
      asp.yaw_rate_rad_s = fw.yaw_rate_rad_s;
      uorb.publish("control/apm", "APM_CTRL roll=" + std::to_string(fw.roll_rad) +
                                       " pitch=" + std::to_string(fw.pitch_rad));
    }
  }

  const ControlTorque torque = att_ctrl_.update(attitude, asp, dt_s);
  quad_out_ = motors_.mix_quad(static_cast<float>(asp.thrust_base), torque);
  uorb.publish("control/attitude", "ATT_CTRL vtol roll=" + std::to_string(torque.roll));
  uorb.publish("vtol/actuators", format_motors_quad(quad_out_));
  return quad_out_;
}

BoatActuators ControlCore::update_boat(bool armed, bool fence_breach, const Attitude &attitude,
                                       const LocalPosition &pos, const VehicleSetpoints &sp, double dt_s, UORB &uorb) {
  if (!armed || fence_breach) {
    boat_out_ = BoatActuators{};
    last_ar_motors_ = ar_motors_.update(0.0F, 0.0F, false);
    uorb.publish("control/ar_attitude", "ARATC disarmed");
    uorb.publish("actuators/boat", "left=0 right=0");
    return boat_out_;
  }

  ArAttitudeOutput ar_out{};
  if (sp.manual_boat) {
    ar_out = ar_att_ctrl_.update_manual(sp.boat_forward, sp.boat_turn, true);
  } else {
    ar_out = ar_att_ctrl_.update_nav(attitude, pos, sp.desired_speed_m_s, sp.desired_turn_rate_rad_s, true, dt_s);
  }
  uorb.publish("control/ar_attitude", format_ar_attitude(ar_out));

  last_ar_motors_ = ar_motors_.update(ar_out.throttle, ar_out.steering, true);
  boat_out_.left = last_ar_motors_.left;
  boat_out_.right = last_ar_motors_.right;
  uorb.publish("actuators/ar_motors", format_ar_motors(last_ar_motors_));
  uorb.publish("actuators/boat",
               "left=" + std::to_string(boat_out_.left) + " right=" + std::to_string(boat_out_.right));
  return boat_out_;
}

BoatActuators ControlCore::update_sailboat(bool armed, bool fence_breach, const Attitude &attitude,
                                           const LocalPosition &pos, const VehicleSetpoints &sp,
                                           const WindSample &wind, double dt_s, UORB &uorb) {
  if (!armed || fence_breach) {
    boat_out_ = BoatActuators{};
    last_ar_motors_ = ar_motors_.update(0.0F, 0.0F, false);
    uorb.publish("control/sailboat", "SAIL disarmed");
    return boat_out_;
  }

  const auto sail = sailboat_.update(attitude, wind, static_cast<float>(sp.desired_turn_rate_rad_s),
                                     static_cast<float>(sp.desired_speed_m_s), sp.manual_boat, sp.boat_forward,
                                     sp.boat_turn, true);
  uorb.publish("control/sailboat", format_sailboat(sail));

  last_ar_motors_ = ar_motors_.update(sail.throttle, sail.steering, true);
  boat_out_.left = last_ar_motors_.left;
  boat_out_.right = last_ar_motors_.right;
  uorb.publish("actuators/ar_motors", format_ar_motors(last_ar_motors_));
  uorb.publish("actuators/boat",
               "left=" + std::to_string(boat_out_.left) + " right=" + std::to_string(boat_out_.right));
  (void)pos;
  (void)dt_s;
  return boat_out_;
}

BoatActuators ControlCore::update_subsea(bool armed, bool fence_breach, const VehicleSetpoints &sp, UORB &uorb) {
  if (!armed || fence_breach) {
    boat_out_ = BoatActuators{};
  } else {
    boat_out_ = motors_.mix_boat(sp.subsea_thrust, sp.subsea_yaw);
  }
  uorb.publish("actuators/subsea",
               "left=" + std::to_string(boat_out_.left) + " right=" + std::to_string(boat_out_.right));
  return boat_out_;
}

} // namespace vrp
