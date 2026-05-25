#pragma once
/**
 * @module  libraries/VRP_Motors
 * @dal     B
 * @req     VRP-LLRD-AP_Motors
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_Motors {
public:
  bool init();
  MotorOutputQuad mix_quad(float thrust, const ControlTorque &torque) const;
  BoatActuators mix_boat(float forward, float turn) const;

  static float clamp01(float v);
};

} // namespace vrp
