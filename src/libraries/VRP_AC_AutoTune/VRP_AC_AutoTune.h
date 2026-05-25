#pragma once
/**
 * @module  libraries/VRP_AC_AutoTune
 * @dal     C
 * @req     VRP-LLRD-AC_AutoTune
 * @parity  ArduPilot AC_AutoTune — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct AutoTuneState {
  bool active{false};
  uint8_t step{0};
  uint8_t pct{0};
};

class VRP_AC_AutoTune {
public:
  bool init();
  AutoTuneState update(bool armed, float aux1, uint64_t tick);

private:
  uint8_t step_{0};
};

std::string format_autotune(const AutoTuneState &s);

} // namespace vrp
