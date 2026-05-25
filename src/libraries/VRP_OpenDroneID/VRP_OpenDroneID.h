#pragma once
/**
 * @module  libraries/VRP_OpenDroneID
 * @dal     C
 * @req     VRP-LLRD-AP_OpenDroneID
 * @parity  ArduPilot AP_OpenDroneID — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_OpenDroneID {
public:
  bool init();
  std::string broadcast(const GpsSample &gps, bool armed, const std::string &mode, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

} // namespace vrp
