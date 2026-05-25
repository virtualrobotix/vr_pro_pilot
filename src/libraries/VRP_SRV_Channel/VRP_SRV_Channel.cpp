#include "libraries/VRP_SRV_Channel/VRP_SRV_Channel.h"

namespace vrp {

bool VRP_SRV_Channel::init() { return true; }

uint16_t VRP_SRV_Channel::pwm_from_unit(float v) {
  if (v < 0.0F) {
    v = 0.0F;
  }
  if (v > 1.0F) {
    v = 1.0F;
  }
  return static_cast<uint16_t>(1000.0F + v * 1000.0F);
}

ServoOutput VRP_SRV_Channel::map_quad(const MotorOutputQuad &motors) const {
  ServoOutput out{};
  out.motor1_us = pwm_from_unit(motors.m1);
  out.motor2_us = pwm_from_unit(motors.m2);
  out.motor3_us = pwm_from_unit(motors.m3);
  out.motor4_us = pwm_from_unit(motors.m4);
  out.tilt_us = 1500;
  out.elevon_us = 1500;
  return out;
}

ServoOutput VRP_SRV_Channel::map_vtol(const MotorOutputQuad &motors, const std::string &phase) const {
  ServoOutput out = map_quad(motors);
  if (phase == "TRANSITION") {
    out.tilt_us = 1700;
  } else if (phase == "FW") {
    out.tilt_us = 1900;
    out.elevon_us = 1600;
  } else {
    out.tilt_us = 1100;
  }
  return out;
}

ServoOutput VRP_SRV_Channel::map_boat(const BoatActuators &boat) const {
  ServoOutput out{};
  out.motor1_us = pwm_from_unit(boat.left);
  out.motor2_us = pwm_from_unit(boat.right);
  out.motor3_us = 1000;
  out.motor4_us = 1000;
  return out;
}

} // namespace vrp
