#pragma once
/**
 * @module  libraries/VRP_Servo_Telem
 * @dal     E
 * @req     VRP-LLRD-AP_Servo_Telem
 * @parity  ArduPilot AP_Servo_Telem — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct ServoTelemSample {
  float position_pct{0.0F};
  float voltage_v{0.0F};
  uint8_t temperature_c{0};
  bool valid{false};
};

class VRP_Servo_Telem {
public:
  bool init();
  ServoTelemSample update(float servo_cmd, float bus_v, uint64_t time_ms);

private:
  uint32_t seq_{0};
};

std::string format_servo_telem(const ServoTelemSample &s);

} // namespace vrp
