#include "libraries/VRP_AC_AttitudeControl/VRP_AC_AttitudeControl.h"

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AC_AttitudeControl::init() {
  roll_pid_.reset();
  pitch_pid_.reset();
  return true;
}

ControlTorque VRP_AC_AttitudeControl::update(const Attitude &attitude, const AttitudeSetpoint &sp,
                                             double dt_s) {
  ControlTorque out{};
  out.roll = static_cast<float>(VRP_Math::clamp(roll_pid_.update(sp.roll_rad, attitude.roll_rad, dt_s), -1.0, 1.0));
  out.pitch =
      static_cast<float>(VRP_Math::clamp(pitch_pid_.update(sp.pitch_rad, attitude.pitch_rad, dt_s), -1.0, 1.0));
  out.yaw = static_cast<float>(VRP_Math::clamp(sp.yaw_rate_rad_s * 0.5 - attitude.yaw_rad * 0.05, -1.0, 1.0));
  return out;
}

} // namespace vrp
