#pragma once
/**
 * @module  libraries/VRP_ICEngine
 * @dal     C
 * @req     VRP-LLRD-AP_ICEngine
 * @parity  ArduPilot AP_ICEngine — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct ICEngineState {
  bool running{false};
  uint16_t rpm{0};
  float throttle_pct{0.0F};
};

class VRP_ICEngine {
public:
  bool init();
  ICEngineState update(float throttle, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_icengine(const ICEngineState &s);

} // namespace vrp
