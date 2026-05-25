#include "hal/sitl/HAL_SITL.h"

#include <thread>

namespace vrp {

HALSITL::HALSITL() : start_(std::chrono::steady_clock::now()) {}

std::string HALSITL::name() const { return "HAL_SITL"; }

void HALSITL::init() { start_ = std::chrono::steady_clock::now(); }

void HALSITL::sleep_ms(uint32_t ms) { std::this_thread::sleep_for(std::chrono::milliseconds(ms)); }

uint64_t HALSITL::now_ms() const {
  const auto delta = std::chrono::steady_clock::now() - start_;
  return static_cast<uint64_t>(std::chrono::duration_cast<std::chrono::milliseconds>(delta).count());
}

void HALSITL::run_once(const std::function<void()> &loop_fn) { loop_fn(); }

} // namespace vrp
