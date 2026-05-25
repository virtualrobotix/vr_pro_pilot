#pragma once
/**
 * @module  libraries/VRP_Stats
 * @dal     C
 * @req     VRP-LLRD-AP_Stats
 * @parity  ArduPilot AP_Stats — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_Stats {
public:
  bool init();
  void update(uint64_t tick, bool armed, const LocalPosition &pos, double dt_s);
  std::string summary() const;

private:
  uint64_t loop_count_{0};
  uint64_t armed_ticks_{0};
  double distance_m_{0.0};
  bool have_prev_{false};
  double prev_x_{0.0};
  double prev_y_{0.0};
};

} // namespace vrp
