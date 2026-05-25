#pragma once
/**
 * @module  libraries/VRP_InertialSensor
 * @dal     B
 * @req     VRP-LLRD-AP_InertialSensor
 * @parity  ArduPilot AP_InertialSensor
 * @status  partial
 */
/**
 * @module  libraries/VRP_InertialSensor
 * @dal     B
 * @req     VRP-LLRD-AP_InertialSensor
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_InertialSensor {
public:
  bool init();
  ImuSample update(const SensorGroundTruth &truth, uint64_t time_us, double dt_s);

  const ImuSample &last() const { return last_; }

private:
  ImuSample last_{};
  double prev_yaw_rad_{0.0};
  bool have_prev_{false};
};

} // namespace vrp
