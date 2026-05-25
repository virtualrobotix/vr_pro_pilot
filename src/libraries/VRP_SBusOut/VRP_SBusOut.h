#pragma once
/**
 * @module  libraries/VRP_SBusOut
 * @dal     C
 * @req     VRP-LLRD-AP_SBusOut
 * @parity  ArduPilot AP_SBusOut — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RcChannels;

struct SBusOutState {
  uint8_t channels{0};
  uint32_t frames{0};
  bool active{false};
};

class VRP_SBusOut {
public:
  bool init();
  SBusOutState update(const RcChannels &rc, bool armed, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_sbus_out(const SBusOutState &s);

} // namespace vrp
