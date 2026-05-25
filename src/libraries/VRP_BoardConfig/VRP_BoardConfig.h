#pragma once
/**
 * @module  libraries/VRP_BoardConfig
 * @dal     C
 * @req     VRP-LLRD-AP_BoardConfig
 * @parity  ArduPilot AP_BoardConfig — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct BoardConfigState {
  bool ok{false};
  uint8_t board_id{0};
  uint8_t rev{0};
};

class VRP_BoardConfig {
public:
  bool init();
  BoardConfigState status(uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_board_config(const BoardConfigState &s);

} // namespace vrp
