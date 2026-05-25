#pragma once
/**
 * @module  libraries/VRP_Radio
 * @dal     C
 * @req     VRP-LLRD-AP_Radio
 * @parity  ArduPilot AP_Radio — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RssiSample;

struct RadioState {
  uint8_t rssi_pct{0};
  bool bound{false};
  bool valid{false};
};

class VRP_Radio {
public:
  bool init();
  RadioState update(const RssiSample &rssi, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_radio(const RadioState &s);

} // namespace vrp
