#pragma once
/**
 * @module  modules/ekf2/EKF2
 * @dal     B
 * @req     VRP-LLRD-AP_NavEKF2
 * @parity  ArduPilot AP_NavEKF2
 * @status  partial
 */

#include <string>

namespace vrp {

class EKF2 {
public:
  std::string update(double x, double y, double z) const;
};

} // namespace vrp
