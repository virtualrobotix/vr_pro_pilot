#include "libraries/VRP_AR_AttitudeControl/VRP_AR_AttitudeControl.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AR_AttitudeControl::init(double max_speed_m_s) {
  max_speed_m_s_ = VRP_Math::clamp(max_speed_m_s, 0.5, 20.0);
  steer_rate_pid_.reset();
  speed_pid_.reset();
  return true;
}

ArAttitudeOutput VRP_AR_AttitudeControl::update_manual(float throttle, float steering, bool armed) {
  ArAttitudeOutput out{};
  out.active = armed;
  if (!armed) {
    return out;
  }
  out.throttle = VRP_Math::clamp(throttle, -1.0F, 1.0F);
  out.steering = VRP_Math::clamp(steering, -1.0F, 1.0F);
  return out;
}

ArAttitudeOutput VRP_AR_AttitudeControl::update_nav(const Attitude &attitude, const LocalPosition &pos,
                                                    double desired_speed_m_s, double desired_turn_rate_rad_s,
                                                    bool armed, double dt_s) {
  ArAttitudeOutput out{};
  out.active = armed;
  if (!armed) {
    steer_rate_pid_.reset();
    speed_pid_.reset();
    return out;
  }

  const double speed = std::sqrt(VRP_Math::sq(pos.vx) + VRP_Math::sq(pos.vy));
  const double yaw_rate = pos.valid ? VRP_Math::wrap_pi(attitude.yaw_rad - prev_yaw_) / std::max(dt_s, 1e-3) : 0.0;
  prev_yaw_ = attitude.yaw_rad;

  const double steer_cmd = steer_rate_pid_.update(desired_turn_rate_rad_s, yaw_rate, dt_s);
  const double speed_target = VRP_Math::clamp(desired_speed_m_s, 0.0, max_speed_m_s_);
  const double throttle_cmd = speed_pid_.update(speed_target, speed, dt_s);

  out.speed_m_s = speed;
  out.turn_rate_rad_s = yaw_rate;
  out.steering = static_cast<float>(VRP_Math::clamp(steer_cmd + desired_turn_rate_rad_s * 0.25, -1.0, 1.0));
  out.throttle = static_cast<float>(VRP_Math::clamp(throttle_cmd + speed_target / std::max(max_speed_m_s_, 0.5), -0.2, 1.0));
  return out;
}

std::string format_ar_attitude(const ArAttitudeOutput &o) {
  std::ostringstream oss;
  oss << "ARATC active=" << (o.active ? 1 : 0) << " thr=" << o.throttle << " steer=" << o.steering
      << " spd=" << o.speed_m_s;
  return oss.str();
}

} // namespace vrp
