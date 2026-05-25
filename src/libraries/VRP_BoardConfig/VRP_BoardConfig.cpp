#include "libraries/VRP_BoardConfig/VRP_BoardConfig.h"

#include <cstdlib>
#include <sstream>

#if defined(VRP_TARGET_CHIBIOS) && defined(VRP_BOARD_V54)
#include "hal/chibios/hwdef/VRBrain-v54.h"
#elif defined(VRP_TARGET_ESP32) && defined(VRP_BOARD_VRESP32_V1)
#include "hal/esp32/hwdef/VREsp32-v1.h"
#endif

namespace vrp {

namespace {

uint8_t board_id_from_product(const char *product_hex) {
  if (product_hex == nullptr || product_hex[0] == '\0') {
    return 0;
  }
  return static_cast<uint8_t>(std::strtoul(product_hex, nullptr, 0) & 0xFF);
}

} // namespace

bool VRP_BoardConfig::init() {
  seq_ = 0;
  return true;
}

BoardConfigState VRP_BoardConfig::status(uint64_t tick) {
  BoardConfigState out{};
  out.ok = true;
#if defined(VRP_TARGET_CHIBIOS) && defined(VRP_BOARD_V54)
  out.board_id = board_id_from_product(VRP_USB_PRODUCT);
#elif defined(VRP_TARGET_ESP32) && defined(VRP_BOARD_VRESP32_V1)
  out.board_id = board_id_from_product(VRP_USB_PRODUCT);
#else
  out.board_id = 54;
#endif
  out.rev = static_cast<uint8_t>(1 + (tick % 3));
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_board_config(const BoardConfigState &s) {
  std::ostringstream oss;
  oss << "BOARD ok=" << (s.ok ? 1 : 0) << " id=" << static_cast<int>(s.board_id)
      << " rev=" << static_cast<int>(s.rev);
  return oss.str();
}

} // namespace vrp
