#pragma once
/** @module libraries/VRP_HAL_ESP32 @dal     E @status  partial */
#include <string>

namespace vrp {

struct HalEsp32State {
  bool ok{false};
  const char *backend{"esp32"};
};

class VRP_HAL_ESP32 {
public:
  bool init();
  HalEsp32State status() const;

private:
  bool ok_{false};
};

std::string format_hal_esp32(const HalEsp32State &s);

} // namespace vrp
