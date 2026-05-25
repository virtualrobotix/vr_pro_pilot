#pragma once
/**
 * @module  libraries/VRP_AR_AttitudeControl
 * @dal     B
 * @req     VRP-LLRD-APM_Control
 * @status  partial
 */
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_PID/VRP_PID.h"

namespace vrp {

struct ArAttitudeOutput {
  float throttle{0.0F};
  float steering{0.0F};
  double speed_m_s{0.0};
  double turn_rate_rad_s{0.0};
  bool active{false};
};

class VRP_AR_AttitudeControl {
public:
  bool init(double max_speed_m_s);
  ArAttitudeOutput update_manual(float throttle, float steering, bool armed);
  ArAttitudeOutput update_nav(const Attitude &attitude, const LocalPosition &pos, double desired_speed_m_s,
                              double desired_turn_rate_rad_s, bool armed, double dt_s);

private:
  double max_speed_m_s_{2.0};
  double prev_yaw_{0.0};
  PIDController steer_rate_pid_{0.2, 0.2, 0.0, 1.0};
  PIDController speed_pid_{0.2, 0.2, 0.0, 1.0};
};

std::string format_ar_attitude(const ArAttitudeOutput &o);

} // namespace vrp
