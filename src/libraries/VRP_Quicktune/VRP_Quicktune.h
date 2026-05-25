#pragma once
/**
 * @module  libraries/VRP_Quicktune
 * @dal     D
 * @req     VRP-LLRD-AP_Quicktune
 * @parity  ArduPilot AP_Quicktune — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct QuicktuneState {
  uint8_t step{0};
  uint8_t pct{0};
  bool active{false};
};

class VRP_Quicktune {
public:
  bool init();
  QuicktuneState update(bool armed, float aux1, uint64_t tick);

private:
  uint8_t step_{0};
};

std::string format_quicktune(const QuicktuneState &s);

} // namespace vrp
