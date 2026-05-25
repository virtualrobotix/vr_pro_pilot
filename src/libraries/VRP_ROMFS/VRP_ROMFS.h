#pragma once
/**
 * @module  libraries/VRP_ROMFS
 * @dal     C
 * @req     VRP-LLRD-AP_ROMFS
 * @parity  ArduPilot AP_ROMFS — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RomfsState {
  uint16_t files{0};
  uint32_t size_kb{0};
  bool mounted{false};
};

class VRP_ROMFS {
public:
  bool init();
  RomfsState status(uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_romfs(const RomfsState &s);

} // namespace vrp
