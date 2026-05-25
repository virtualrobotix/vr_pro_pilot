#pragma once
/**
 * @module  libraries/VRP_AR_Motors
 * @dal     B
 * @req     VRP-LLRD-AR_Motors
 * @parity  ArduPilot AR_Motors — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct ArMotorsState {
  float left{0.0F};
  float right{0.0F};
  bool active{false};
};

class VRP_AR_Motors {
public:
  bool init();
  ArMotorsState update(float throttle, float steer, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_ar_motors(const ArMotorsState &s);

} // namespace vrp
