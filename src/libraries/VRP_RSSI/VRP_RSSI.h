#pragma once
/**
 * @module  libraries/VRP_RSSI
 * @dal     E
 * @req     VRP-LLRD-AP_RSSI
 * @parity  ArduPilot AP_RSSI — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RssiSample {
  uint8_t pct{0};
  bool valid{false};
};

class VRP_RSSI {
public:
  bool init();
  RssiSample update(uint64_t tick, bool gcs_link);

private:
  uint8_t base_pct_{92};
};

std::string format_rssi(const RssiSample &s);

} // namespace vrp
