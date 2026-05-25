#include "hal/esp32/HAL_ESP32.h"

#include <sstream>
#include <thread>

#ifdef VRP_TARGET_ESP32
#if defined(VRP_BOARD_VRESP32_V1)
#include "hal/esp32/hwdef/VREsp32-v1.h"
#endif
#endif

namespace vrp {

HALESP32::HALESP32() : start_(std::chrono::steady_clock::now()) {}

std::string HALESP32::name() const { return "HAL_ESP32"; }

void HALESP32::init() {
  start_ = std::chrono::steady_clock::now();
#if defined(VRP_TARGET_ESP32) && defined(VRP_BOARD_VRESP32_V1)
  board_info_ = std::string(VRP_APJ_BOARD_ID) + " mcu=" + VRP_MCU;
  wifi_enabled_ = VRP_WIFI_ENABLED != 0;
#else
  board_info_ = "AP_HW_VRESP32_V1 mcu=ESP32 sim";
  wifi_enabled_ = true;
#endif
}

std::string HALESP32::board_info() const { return board_info_; }

std::string HALESP32::flash_info() const {
#if defined(VRP_TARGET_ESP32) && defined(VRP_BOARD_VRESP32_V1)
  std::ostringstream oss;
  oss << "FLASH size=" << VRP_FLASH_SIZE << " storage=" << VRP_STORAGE << " xtal=" << VRP_XTAL_HZ;
  return oss.str();
#endif
  return "FLASH size=4194304 storage=SPI_FLASH sim";
}

std::string HALESP32::wifi_info() const {
  std::ostringstream oss;
  oss << "WIFI enabled=" << (wifi_enabled_ ? 1 : 0) << " mode=AP+STA sim";
  return oss.str();
}

void HALESP32::sleep_ms(uint32_t ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

uint64_t HALESP32::now_ms() const {
  const auto delta = std::chrono::steady_clock::now() - start_;
  return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(delta).count());
}

void HALESP32::run_once(const std::function<void()> &loop_fn) { loop_fn(); }

} // namespace vrp
