#pragma once
/**
 * @module  libraries/VRP_IRLock
 * @dal     C
 * @req     VRP-LLRD-AP_IRLock
 * @parity  ArduPilot AP_IRLock — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct IRLockState {
  float x_m{0.0F};
  float y_m{0.0F};
  bool target_valid{false};
};

class VRP_IRLock {
public:
  bool init();
  IRLockState update(bool armed, double pos_x, double pos_y, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_irlock(const IRLockState &s);

} // namespace vrp
