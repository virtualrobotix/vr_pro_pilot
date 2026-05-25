#pragma once
/**
 * @module  libraries/VRP_HAL_Empty
 * @dal     E
 * @req     VRP-LLRD-AP_HAL_Empty
 * @parity  ArduPilot AP_HAL_Empty — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct HalEmptyState {
  bool ok{false};
};

class VRP_HAL_Empty {
public:
  bool init();
  HalEmptyState status() const;

private:
  bool ok_{false};
};

std::string format_hal_empty(const HalEmptyState &s);

} // namespace vrp
