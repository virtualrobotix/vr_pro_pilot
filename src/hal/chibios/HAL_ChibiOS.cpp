#include "hal/chibios/HAL_ChibiOS.h"

#include <thread>

#ifdef VRP_TARGET_CHIBIOS
#if defined(VRP_BOARD_V54)
#include "hal/chibios/hwdef/VRBrain-v54.h"
#endif
#endif

namespace vrp {

HALChibiOS::HALChibiOS() : start_(std::chrono::steady_clock::now()) {}

std::string HALChibiOS::name() const { return "HAL_ChibiOS"; }

void HALChibiOS::init() {
  start_ = std::chrono::steady_clock::now();
#if defined(VRP_TARGET_CHIBIOS) && defined(VRP_BOARD_V54)
  board_info_ = std::string(VRP_APJ_BOARD_ID) + " mcu=" + VRP_MCU;
#else
  board_info_ = "HAL_ChibiOS_HOST sim";
#endif
}

std::string HALChibiOS::board_info() const { return board_info_; }

std::string HALChibiOS::flash_info() const {
#if defined(VRP_TARGET_CHIBIOS) && defined(VRP_BOARD_V54)
  return "FLASH base=0x080E0000 sectors=2 size=16384 mcu=STM32F427";
#endif
  return "FLASH sim sectors=2 size=16384";
}

void HALChibiOS::sleep_ms(uint32_t ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

uint64_t HALChibiOS::now_ms() const {
  const auto delta = std::chrono::steady_clock::now() - start_;
  return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(delta).count());
}

void HALChibiOS::run_once(const std::function<void()> &loop_fn) { loop_fn(); }

} // namespace vrp
