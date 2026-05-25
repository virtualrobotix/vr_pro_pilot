#pragma once
/**
 * @module  libraries/VRP_LTM_Telem
 * @dal     E
 * @req     VRP-LLRD-AP_LTM_Telem
 * @parity  ArduPilot AP_LTM_Telem — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_LTM_Telem {
public:
  bool init();
  std::string update(const LocalPosition &pos, const GpsSample &gps, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

} // namespace vrp
