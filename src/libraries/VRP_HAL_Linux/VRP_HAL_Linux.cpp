#include "libraries/VRP_HAL_Linux/VRP_HAL_Linux.h"

#include <sstream>

namespace vrp {

bool VRP_HAL_Linux::init() {
  ok_ = true;
  return true;
}

HalLinuxState VRP_HAL_Linux::status() const {
  HalLinuxState out{};
  out.ok = ok_;
  out.backend = "linux";
  return out;
}

std::string format_hal_linux(const HalLinuxState &s) {
  std::ostringstream oss;
  oss << "HALLX ok=" << (s.ok ? 1 : 0) << " backend=" << s.backend;
  return oss.str();
}

} // namespace vrp
