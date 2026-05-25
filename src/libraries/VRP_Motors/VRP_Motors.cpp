#include "libraries/VRP_Motors/VRP_Motors.h"

#include <cmath>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Motors::init(double max_tilt_deg) {
  max_tilt_rad_ = VRP_Math::deg_to_rad(max_tilt_deg);
  return true;
}

float VRP_Motors::clamp01(float v) {
  if (v < 0.0F) {
    return 0.0F;
  }
  if (v > 1.0F) {
    return 1.0F;
  }
  return v;
}

float VRP_Motors::thrust_linearize(float thrust, float hover, float expo) {
  const float t = clamp01(thrust);
  const float h = clamp01(hover);
  if (t <= h) {
    return clamp01(t * (h / std::max(h, 0.01F)));
  }
  const float above = (t - h) / std::max(1.0F - h, 0.01F);
  return clamp01(h + std::pow(above, expo) * (1.0F - h));
}

MotorOutputQuad VRP_Motors::mix_quad(float thrust, const ControlTorque &torque, float spool,
                                     float yaw_headroom) const {
  const float thr = thrust_linearize(clamp01(thrust * spool));
  const float yaw = VRP_Math::clamp(torque.yaw, -yaw_headroom, yaw_headroom);
  const float roll = VRP_Math::clamp(torque.roll, -static_cast<float>(max_tilt_rad_),
                                     static_cast<float>(max_tilt_rad_));
  const float pitch = VRP_Math::clamp(torque.pitch, -static_cast<float>(max_tilt_rad_),
                                      static_cast<float>(max_tilt_rad_));
  MotorOutputQuad out{};
  out.m1 = clamp01(thr + roll + pitch - yaw);
  out.m2 = clamp01(thr - roll + pitch + yaw);
  out.m3 = clamp01(thr - roll - pitch - yaw);
  out.m4 = clamp01(thr + roll - pitch + yaw);
  return out;
}

BoatActuators VRP_Motors::mix_boat(float forward, float turn) const {
  BoatActuators out{};
  out.left = clamp01(forward - turn);
  out.right = clamp01(forward + turn);
  return out;
}

} // namespace vrp
