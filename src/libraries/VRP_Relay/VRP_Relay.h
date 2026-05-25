#pragma once
/**
 * @module  libraries/VRP_Relay
 * @dal     C
 * @req     VRP-LLRD-AP_Relay
 * @parity  ArduPilot AP_Relay — clean-room BSD rewrite
 * @status  partial
 */
#include <array>
#include <cstdint>
#include <string>

namespace vrp {

class VRP_Relay {
public:
  bool init();
  std::array<uint8_t, 4> update(bool armed, uint64_t tick);

private:
  std::array<uint8_t, 4> last_{};
};

std::string format_relay(const std::array<uint8_t, 4> &channels);

} // namespace vrp
