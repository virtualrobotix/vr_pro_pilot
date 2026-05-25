#pragma once
/** @module libraries/VRP_HAL_ESP32 @dal     E @status  partial */
#include <string>

namespace vrp {

struct HalEsp32State {
  bool ok{false};
  const char *backend{"esp32"};
  const char *board_id{""};
  const char *mcu{"ESP32"};
};

class VRP_HAL_ESP32 {
public:
  bool init();
  HalEsp32State status() const;

private:
  bool ok_{false};
  const char *board_id_{""};
  const char *mcu_{"ESP32"};
};

std::string format_hal_esp32(const HalEsp32State &s);

} // namespace vrp
