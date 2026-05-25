#include "libraries/VRP_APM_Control/VRP_APM_Control.h"

#include <cmath>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

namespace {
double wrap_pi(double rad) {
  while (rad > M_PI) {
    rad -= 2.0 * M_PI;
  }
  while (rad < -M_PI) {
    rad += 2.0 * M_PI;
  }
  return rad;
}
} // namespace

bool VRP_APM_Control::init() { return true; }

FwControlSetpoint VRP_APM_Control::update(const Attitude &attitude, const FwNavSetpoint &nav,
                                            const FwControlSetpoint &tecs_sp, double dt_s) {
  FwControlSetpoint out{};
  out.pitch_rad = tecs_sp.pitch_rad;
  out.yaw_rate_rad_s = tecs_sp.yaw_rate_rad_s;

  if (nav.valid) {
    const double bearing_err = wrap_pi(nav.bearing_rad - attitude.yaw_rad);
    const double target_roll = VRP_Math::clamp(bearing_err * 1.4, -0.45, 0.45);
    const double roll_torque = roll_pid_.update(target_roll, attitude.roll_rad, dt_s);
    out.roll_rad = VRP_Math::clamp(attitude.roll_rad + roll_torque * dt_s, -0.5, 0.5);
    out.yaw_rate_rad_s = VRP_Math::clamp(bearing_err * 0.35, -0.6, 0.6);
  }

  const double pitch_torque = pitch_pid_.update(out.pitch_rad, attitude.pitch_rad, dt_s);
  out.pitch_rad = VRP_Math::clamp(attitude.pitch_rad + pitch_torque * dt_s, -0.6, 0.35);
  (void)nav.speed_m_s;
  return out;
}

} // namespace vrp
