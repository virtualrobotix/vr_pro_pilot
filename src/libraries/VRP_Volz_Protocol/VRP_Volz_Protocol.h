#pragma once
/**
 * @module  libraries/VRP_Volz_Protocol
 * @dal     C
 * @req     VRP-LLRD-AP_Volz_Protocol
 * @parity  ArduPilot AP_Volz_Protocol — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct VolzState {
  uint8_t servo_id{0};
  float position_deg{0.0F};
  bool valid{false};
};

class VRP_Volz_Protocol {
public:
  bool init();
  VolzState update(float command, bool armed, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_volz(const VolzState &s);

} // namespace vrp
