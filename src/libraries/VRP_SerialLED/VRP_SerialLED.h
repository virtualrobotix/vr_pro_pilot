#pragma once
/**
 * @module  libraries/VRP_SerialLED
 * @dal     C
 * @req     VRP-LLRD-AP_SerialLED
 * @parity  ArduPilot AP_SerialLED — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct SerialLedState {
  uint16_t pixels{0};
  uint8_t pattern{0};
  bool active{false};
};

class VRP_SerialLED {
public:
  bool init();
  SerialLedState update(bool armed, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_serial_led(const SerialLedState &s);

} // namespace vrp
