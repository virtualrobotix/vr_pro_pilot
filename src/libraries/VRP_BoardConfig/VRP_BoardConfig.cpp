#include "libraries/VRP_BoardConfig/VRP_BoardConfig.h"

#include <sstream>

namespace vrp {

bool VRP_BoardConfig::init() {
  seq_ = 0;
  return true;
}

BoardConfigState VRP_BoardConfig::status(uint64_t tick) {
  BoardConfigState out{};
  out.ok = true;
  out.board_id = 54;
  out.rev = static_cast<uint8_t>(1 + (tick % 3));
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_board_config(const BoardConfigState &s) {
  std::ostringstream oss;
  oss << "BOARD ok=" << (s.ok ? 1 : 0) << " id=" << static_cast<int>(s.board_id)
      << " rev=" << static_cast<int>(s.rev);
  return oss.str();
}

} // namespace vrp
