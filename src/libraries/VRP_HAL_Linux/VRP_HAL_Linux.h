#pragma once
/**
 * @module  libraries/VRP_HAL_Linux
 * @dal     E
 * @req     VRP-LLRD-AP_HAL_Linux
 * @parity  ArduPilot AP_HAL_Linux — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct HalLinuxState {
  bool ok{false};
  const char *backend{"linux"};
};

class VRP_HAL_Linux {
public:
  bool init();
  HalLinuxState status() const;

private:
  bool ok_{false};
};

std::string format_hal_linux(const HalLinuxState &s);

} // namespace vrp
