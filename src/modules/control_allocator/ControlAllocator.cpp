#include "modules/control_allocator/ControlAllocator.h"

#include "libraries/VRP_Motors/VRP_Motors.h"

namespace vrp {

namespace {
VRP_Motors g_motors;
}

std::array<float, 4> ControlAllocator::allocate_quad(float thrust, float yaw) const {
  ControlTorque t{};
  t.yaw = yaw;
  const MotorOutputQuad out = g_motors.mix_quad(thrust, t);
  return {out.m1, out.m2, out.m3, out.m4};
}

std::string ControlAllocator::allocate_boat(float forward, float turn) const {
  const BoatActuators out = g_motors.mix_boat(forward, turn);
  return "left=" + std::to_string(out.left) + " right=" + std::to_string(out.right);
}

} // namespace vrp
