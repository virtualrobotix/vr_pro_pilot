#pragma once
/**
 * @module  libraries/VRP_SRV_Channel
 * @dal     B
 * @req     VRP-LLRD-SRV_Channel
 * @parity  ArduPilot SRV_Channel
 * @status  partial
 */
/**
 * @module  libraries/VRP_SRV_Channel
 * @dal     B
 * @req     VRP-LLRD-SRV_Channel
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_SRV_Channel {
public:
  bool init();
  ServoOutput map_quad(const MotorOutputQuad &motors) const;
  ServoOutput map_vtol(const MotorOutputQuad &motors, const std::string &phase) const;
  ServoOutput map_boat(const BoatActuators &boat) const;

private:
  static uint16_t pwm_from_unit(float v);
};

} // namespace vrp
