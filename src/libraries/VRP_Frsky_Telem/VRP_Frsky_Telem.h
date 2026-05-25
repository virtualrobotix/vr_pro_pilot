#pragma once
/**
 * @module  libraries/VRP_Frsky_Telem
 * @dal     E
 * @req     VRP-LLRD-AP_Frsky_Telem
 * @parity  ArduPilot AP_Frsky_Telem — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_Frsky_Telem {
public:
  bool init();
  std::string update(const std::string &mode, const Attitude &att, const BatteryStatus &batt,
                     const LocalPosition &pos, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

} // namespace vrp
