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
  bool init(double max_tilt_deg = 35.0);
  MotorOutputQuad mix_quad(float thrust, const ControlTorque &torque, float spool = 1.0F,
                           float yaw_headroom = 0.15F) const;
  static float thrust_linearize(float thrust, float hover = 0.55F, float expo = 0.65F);
  BoatActuators mix_boat(float forward, float turn) const;

  static float clamp01(float v);

private:
  double max_tilt_rad_{0.61};
};

} // namespace vrp
