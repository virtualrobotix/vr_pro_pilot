#pragma once
/**
 * @module  libraries/VRP_Baro
 * @dal     B
 * @req     VRP-LLRD-AP_Baro
 * @parity  ArduPilot AP_Baro
 * @status  partial
 */
/**
 * @module  libraries/VRP_Baro
 * @dal     B
 * @req     VRP-LLRD-AP_Baro
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_Baro {
public:
  bool init();
  BaroSample update(double alt_m, uint64_t time_us);

private:
  static constexpr double kSeaLevelPa = 101325.0;
};

} // namespace vrp
