#pragma once
/**
 * @module  libraries/VRP_AC_Autorotation
 * @dal     B
 * @req     VRP-LLRD-AC_Autorotation
 * @parity  ArduPilot AC_Autorotation — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct AutorotationState {
  bool active{false};
  uint8_t phase{0};
  uint16_t rpm{0};
};

class VRP_AC_Autorotation {
public:
  bool init();
  AutorotationState update(bool armed, bool rtl_active, float throttle);

private:
  uint32_t seq_{0};
};

std::string format_autorotation(const AutorotationState &s);

} // namespace vrp
