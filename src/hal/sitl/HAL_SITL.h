#pragma once
/**
 * @module  hal/sitl/HAL_SITL
 * @dal     C
 * @req     VRP-LLRD-AP_HAL_SITL
 * @parity  ArduPilot AP_HAL_SITL
 * @status  present
 */

#include <chrono>

#include "hal/VRP_HAL.h"

namespace vrp {

class HALSITL final : public IHAL {
public:
  HALSITL();
  std::string name() const override;
  void init() override;
  void sleep_ms(uint32_t ms) override;
  uint64_t now_ms() const override;
  void run_once(const std::function<void()> &loop_fn) override;

private:
  std::chrono::steady_clock::time_point start_;
};

} // namespace vrp
