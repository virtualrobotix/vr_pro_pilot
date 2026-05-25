#include "libraries/VRP_HAL_ESP32/VRP_HAL_ESP32.h"

#include <sstream>

#if defined(VRP_TARGET_ESP32) && defined(VRP_BOARD_VRESP32_V1)
#include "hal/esp32/hwdef/VREsp32-v1.h"
#endif

namespace vrp {

bool VRP_HAL_ESP32::init() {
  ok_ = true;
#if defined(VRP_TARGET_ESP32) && defined(VRP_BOARD_VRESP32_V1)
  board_id_ = VRP_APJ_BOARD_ID;
  mcu_ = VRP_MCU;
#endif
  return true;
}

HalEsp32State VRP_HAL_ESP32::status() const {
  HalEsp32State out{};
  out.ok = ok_;
  out.backend = "esp32";
  out.board_id = board_id_;
  out.mcu = mcu_;
  return out;
}

std::string format_hal_esp32(const HalEsp32State &s) {
  std::ostringstream oss;
  oss << "HALESP ok=" << (s.ok ? 1 : 0) << " backend=" << s.backend;
  if (s.board_id[0] != '\0') {
    oss << " board=" << s.board_id << " mcu=" << s.mcu;
  }
  return oss.str();
}

} // namespace vrp
