#pragma once
/**
 * @module  libraries/VRP_Compass
 * @dal     B
 * @req     VRP-LLRD-AP_Compass
 * @parity  ArduPilot AP_Compass
 * @status  partial
 */
/**
 * @module  libraries/VRP_Compass
 * @dal     B
 * @req     VRP-LLRD-AP_Compass
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_Compass {
public:
  bool init();
  CompassSample update(double yaw_deg, uint64_t time_us);

private:
  double declination_deg_{0.0};
};

} // namespace vrp
