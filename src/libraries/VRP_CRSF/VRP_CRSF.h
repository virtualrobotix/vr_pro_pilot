#pragma once
/**
 * @module  libraries/VRP_CRSF
 * @dal     E
 * @req     VRP-LLRD-AP_CRSF
 * @parity  ArduPilot AP_CRSF — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_RSSI/VRP_RSSI.h"

namespace vrp {

class VRP_CRSF {
public:
  bool init();
  std::string update(const Attitude &att, const BatteryStatus &batt, const RssiSample &rssi, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

} // namespace vrp
