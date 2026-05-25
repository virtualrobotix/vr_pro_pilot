#pragma once
/**
 * @module  libraries/VRP_Hott_Telem
 * @dal     E
 * @req     VRP-LLRD-AP_Hott_Telem
 * @parity  ArduPilot AP_Hott_Telem — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_Hott_Telem {
public:
  bool init();
  std::string update(const Attitude &att, const LocalPosition &pos, const BatteryStatus &batt, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

} // namespace vrp
