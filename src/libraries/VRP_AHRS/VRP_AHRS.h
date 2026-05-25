#pragma once
/**
 * @module  libraries/VRP_AHRS
 * @dal     B
 * @req     VRP-LLRD-AP_AHRS
 * @parity  ArduPilot AP_AHRS
 * @status  partial
 */
/**
 * @module  libraries/VRP_AHRS
 * @dal     B
 * @req     VRP-LLRD-AP_AHRS
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_AHRS {
public:
  bool init();
  Attitude update(const ImuSample &imu, double dt_s);

  const Attitude &attitude() const { return attitude_; }

private:
  Attitude attitude_{};
  bool initialized_{false};
};

} // namespace vrp
