#pragma once
/**
 * @module  libraries/VRP_ESC_Telem
 * @dal     E
 * @req     VRP-LLRD-AP_ESC_Telem
 * @parity  ArduPilot AP_ESC_Telem — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct EscTelemSample {
  float voltage_v{0.0F};
  float current_a{0.0F};
  float rpm{0.0F};
  uint8_t temperature_c{0};
  bool valid{false};
};

class VRP_ESC_Telem {
public:
  bool init();
  EscTelemSample update(float throttle, float battery_v, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

std::string format_esc_telem(const EscTelemSample &s);

} // namespace vrp
