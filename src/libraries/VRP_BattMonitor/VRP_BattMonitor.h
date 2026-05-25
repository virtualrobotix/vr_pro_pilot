#pragma once
/**
 * @module  libraries/VRP_BattMonitor
 * @dal     B
 * @req     VRP-LLRD-AP_BattMonitor
 * @parity  ArduPilot AP_BattMonitor
 * @status  partial
 */
/**
 * @module  libraries/VRP_BattMonitor
 * @dal     B
 * @req     VRP-LLRD-AP_BattMonitor
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_BattMonitor {
public:
  bool init(double min_voltage_v);
  BatteryStatus update(uint64_t tick);

  const BatteryStatus &status() const { return status_; }

private:
  double min_voltage_v_{10.5};
  BatteryStatus status_{};
};

} // namespace vrp
