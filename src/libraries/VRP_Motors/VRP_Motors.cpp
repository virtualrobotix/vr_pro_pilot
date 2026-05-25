#include "libraries/VRP_Motors/VRP_Motors.h"

namespace vrp {

bool VRP_Motors::init() { return true; }

float VRP_Motors::clamp01(float v) {
  if (v < 0.0F) {
    return 0.0F;
  }
  if (v > 1.0F) {
    return 1.0F;
  }
  return v;
}

MotorOutputQuad VRP_Motors::mix_quad(float thrust, const ControlTorque &torque) const {
  MotorOutputQuad out{};
  out.m1 = clamp01(thrust + torque.roll + torque.pitch - torque.yaw);
  out.m2 = clamp01(thrust - torque.roll + torque.pitch + torque.yaw);
  out.m3 = clamp01(thrust - torque.roll - torque.pitch - torque.yaw);
  out.m4 = clamp01(thrust + torque.roll - torque.pitch + torque.yaw);
  return out;
}

BoatActuators VRP_Motors::mix_boat(float forward, float turn) const {
  BoatActuators out{};
  out.left = clamp01(forward - turn);
  out.right = clamp01(forward + turn);
  return out;
}

} // namespace vrp
