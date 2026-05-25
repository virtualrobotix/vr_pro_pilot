#pragma once
/**
 * @module  libraries/VRP_IBus_Telem
 * @dal     E
 * @req     VRP-LLRD-AP_IBus_Telem
 * @parity  ArduPilot AP_IBus_Telem — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_IBus_Telem {
public:
  bool init();
  std::string update(const Attitude &att, const BatteryStatus &batt, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

} // namespace vrp
