#include "libraries/VRP_SerialLED/VRP_SerialLED.h"

#include <sstream>

namespace vrp {

bool VRP_SerialLED::init() {
  seq_ = 0;
  return true;
}

SerialLedState VRP_SerialLED::update(bool armed, uint64_t tick) {
  SerialLedState out{};
  out.active = armed;
  out.pixels = armed ? 24 : 0;
  out.pattern = static_cast<uint8_t>((tick / 50) % 4);
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_serial_led(const SerialLedState &s) {
  std::ostringstream oss;
  oss << "SERLED active=" << (s.active ? 1 : 0) << " px=" << s.pixels << " pat=" << static_cast<int>(s.pattern);
  return oss.str();
}

} // namespace vrp
