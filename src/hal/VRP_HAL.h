#pragma once
/**
 * @module  hal/VRP_HAL
 * @dal     B
 * @req     VRP-LLRD-AP_HAL
 * @parity  ArduPilot AP_HAL
 * @status  present
 */

#include <cstdint>
#include <functional>
#include <string>

namespace vrp {

class IHAL {
public:
  virtual ~IHAL() = default;
  virtual std::string name() const = 0;
  virtual void init() = 0;
  virtual void sleep_ms(uint32_t ms) = 0;
  virtual uint64_t now_ms() const = 0;
  virtual void run_once(const std::function<void()> &loop_fn) = 0;
};

} // namespace vrp
