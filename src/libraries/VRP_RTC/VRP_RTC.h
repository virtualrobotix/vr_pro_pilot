#pragma once
/**
 * @module  libraries/VRP_RTC
 * @dal     C
 * @req     VRP-LLRD-AP_RTC
 * @parity  ArduPilot AP_RTC — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

class VRP_RTC {
public:
  bool init();
  std::string update(uint64_t time_ms);

private:
  uint64_t boot_ms_{0};
  bool have_boot_{false};
};

} // namespace vrp
