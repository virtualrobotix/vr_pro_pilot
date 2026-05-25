#pragma once
/**
 * @module  libraries/VRP_Notify
 * @dal     C
 * @req     VRP-LLRD-AP_Notify
 * @parity  ArduPilot AP_Notify — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

class VRP_Notify {
public:
  bool init();
  std::string update(bool armed, const std::string &mode, uint64_t tick);

private:
  uint32_t seq_{0};
};

} // namespace vrp
