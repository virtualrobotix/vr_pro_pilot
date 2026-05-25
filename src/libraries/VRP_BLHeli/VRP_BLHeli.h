#pragma once
/**
 * @module  libraries/VRP_BLHeli
 * @dal     C
 * @req     VRP-LLRD-AP_BLHeli
 * @parity  ArduPilot AP_BLHeli — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct BLHeliState {
  uint16_t rpm{0};
  float temp_c{0.0F};
  uint8_t esc_count{0};
};

class VRP_BLHeli {
public:
  bool init();
  BLHeliState update(float throttle, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_blheli(const BLHeliState &s);

} // namespace vrp
