#pragma once
/**
 * @module  libraries/VRP_Tuning
 * @dal     D
 * @req     VRP-LLRD-AP_Tuning
 * @parity  ArduPilot AP_Tuning — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RcChannels;

struct TuningState {
  uint8_t channel{0};
  float value{0.0F};
  bool active{false};
};

class VRP_Tuning {
public:
  bool init();
  TuningState update(const RcChannels &rc, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_tuning(const TuningState &s);

} // namespace vrp
