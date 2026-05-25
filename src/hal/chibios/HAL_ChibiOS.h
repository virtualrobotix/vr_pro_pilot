#pragma once
/**
 * @module  hal/chibios/HAL_ChibiOS
 * @dal     B
 * @req     VRP-LLRD-AP_HAL_ChibiOS
 * @parity  ArduPilot AP_HAL_ChibiOS
 * @status  present
 */

#include <chrono>
#include <string>

#include "hal/VRP_HAL.h"

namespace vrp {

class HALChibiOS final : public IHAL {
public:
  HALChibiOS();
  std::string name() const override;
  void init() override;
  void sleep_ms(uint32_t ms) override;
  uint64_t now_ms() const override;
  void run_once(const std::function<void()> &loop_fn) override;
  std::string board_info() const;
  std::string flash_info() const;

private:
  std::chrono::steady_clock::time_point start_;
  std::string board_info_{"HAL_ChibiOS_HOST"};
};

} // namespace vrp
