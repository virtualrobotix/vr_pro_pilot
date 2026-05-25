#include "libraries/VRP_HAL_Empty/VRP_HAL_Empty.h"

#include <sstream>

namespace vrp {

bool VRP_HAL_Empty::init() {
  ok_ = true;
  return true;
}

HalEmptyState VRP_HAL_Empty::status() const {
  HalEmptyState out{};
  out.ok = ok_;
  return out;
}

std::string format_hal_empty(const HalEmptyState &s) {
  std::ostringstream oss;
  oss << "HALEMPTY ok=" << (s.ok ? 1 : 0);
  return oss.str();
}

} // namespace vrp
