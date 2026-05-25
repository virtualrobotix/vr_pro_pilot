#pragma once
/**
 * @module  hal/esp32/HAL_ESP32
 * @dal     B
 * @req     VRP-LLRD-AP_HAL_ESP32
 * @parity  ArduPilot AP_HAL_ESP32
 * @status  present
 */

#include <chrono>
#include <string>

#include "hal/VRP_HAL.h"

namespace vrp {

class HALESP32 final : public IHAL {
public:
  HALESP32();
  std::string name() const override;
  void init() override;
  void sleep_ms(uint32_t ms) override;
  uint64_t now_ms() const override;
  void run_once(const std::function<void()> &loop_fn) override;
  std::string board_info() const;
  std::string flash_info() const;
  std::string wifi_info() const;

private:
  std::chrono::steady_clock::time_point start_;
  std::string board_info_{"HAL_ESP32_HOST"};
  bool wifi_enabled_{false};
};

} // namespace vrp
