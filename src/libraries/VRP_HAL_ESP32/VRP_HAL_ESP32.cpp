#include "libraries/VRP_HAL_ESP32/VRP_HAL_ESP32.h"
#include <sstream>

namespace vrp {

bool VRP_HAL_ESP32::init() {
  ok_ = true;
  return true;
}

HalEsp32State VRP_HAL_ESP32::status() const {
  HalEsp32State out{};
  out.ok = ok_;
  out.backend = "esp32";
  return out;
}

std::string format_hal_esp32(const HalEsp32State &s) {
  std::ostringstream oss;
  oss << "HALESP ok=" << (s.ok ? 1 : 0) << " backend=" << s.backend;
  return oss.str();
}

} // namespace vrp
