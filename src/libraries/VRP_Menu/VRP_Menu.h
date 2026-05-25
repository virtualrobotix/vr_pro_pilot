#pragma once
/**
 * @module  libraries/VRP_Menu
 * @dal     D
 * @req     VRP-LLRD-AP_Menu
 * @parity  ArduPilot AP_Menu — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

class VRP_Menu {
public:
  bool init();
  std::string update(uint64_t tick, bool armed);

private:
  size_t item_{0};
};

} // namespace vrp
