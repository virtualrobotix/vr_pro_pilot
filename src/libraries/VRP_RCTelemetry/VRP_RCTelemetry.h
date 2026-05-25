#pragma once
/**
 * @module  libraries/VRP_RCTelemetry
 * @dal     E
 * @req     VRP-LLRD-AP_RCTelemetry
 * @parity  ArduPilot AP_RCTelemetry — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_RSSI/VRP_RSSI.h"

namespace vrp {

class VRP_RCTelemetry {
public:
  bool init();
  std::string update(const RcChannels &rc, const RssiSample &rssi, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

} // namespace vrp
