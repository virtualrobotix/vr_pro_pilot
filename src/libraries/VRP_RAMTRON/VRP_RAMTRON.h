#pragma once
/**
 * @module  libraries/VRP_RAMTRON
 * @dal     C
 * @req     VRP-LLRD-AP_RAMTRON
 * @parity  ArduPilot AP_RAMTRON — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RamtronState {
  bool ok{false};
  uint32_t base_addr{0};
  uint16_t size_kb{0};
};

class VRP_RAMTRON {
public:
  bool init();
  RamtronState status(uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_ramtron(const RamtronState &s);

} // namespace vrp
