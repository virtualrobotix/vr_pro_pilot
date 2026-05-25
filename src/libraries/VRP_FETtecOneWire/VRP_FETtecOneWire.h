#pragma once
/**
 * @module  libraries/VRP_FETtecOneWire
 * @dal     C
 * @req     VRP-LLRD-AP_FETtecOneWire
 * @parity  ArduPilot AP_FETtecOneWire — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct FETtecState {
  uint8_t esc_count{0};
  float temp_c{0.0F};
  uint16_t rpm{0};
};

class VRP_FETtecOneWire {
public:
  bool init();
  FETtecState update(float throttle, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_fettec(const FETtecState &s);

} // namespace vrp
