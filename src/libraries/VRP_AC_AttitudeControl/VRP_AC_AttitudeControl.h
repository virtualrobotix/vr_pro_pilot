#pragma once
/**
 * @module  libraries/VRP_AC_AttitudeControl
 * @dal     B
 * @req     VRP-LLRD-AC_AttitudeControl
 * @parity  ArduPilot AC_AttitudeControl
 * @status  partial
 */
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_PID/VRP_PID.h"

namespace vrp {

struct PosControlSetpoint {
  double roll_rad{0.0};
  double pitch_rad{0.0};
  double yaw_rate_rad_s{0.0};
  double thrust_base{0.55};
};

class VRP_AC_AttitudeControl {
public:
  bool init(double max_tilt_deg = 35.0);
  void apply_autotune_scale(float scale);
  void set_hover_throttle(float hover) { hover_throttle_ = hover; }
  ControlTorque update(const Attitude &attitude, const AttitudeSetpoint &sp, double dt_s);
  PosControlSetpoint update_pos(const LocalPosition &pos, const WpNavOutput &nav, double target_z_m,
                                double max_tilt_rad, bool alt_hold);

private:
  PIDController roll_pid_{4.5, 0.0, 0.05, 0.3};
  PIDController pitch_pid_{4.5, 0.0, 0.05, 0.3};
  PIDController yaw_pid_{2.0, 0.0, 0.02, 0.2};
  PIDController alt_pid_{1.2, 0.0, 0.08, 0.4};
  double max_tilt_rad_{0.61};
  float tune_scale_{1.0F};
  float hover_throttle_{0.55F};
  double last_vx_{0.0};
  double last_vy_{0.0};
  double last_target_speed_{0.0};
};

std::string format_pos_control(const PosControlSetpoint &sp);

} // namespace vrp
