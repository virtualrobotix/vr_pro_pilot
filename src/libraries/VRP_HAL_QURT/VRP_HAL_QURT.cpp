#include "libraries/VRP_HAL_QURT/VRP_HAL_QURT.h"
#include <sstream>

namespace vrp {

bool VRP_HAL_QURT::init() {
  ok_ = true;
  return true;
}

HalQurtState VRP_HAL_QURT::status() const {
  HalQurtState out{};
  out.ok = ok_;
  out.backend = "qurt";
  return out;
}

std::string format_hal_qurt(const HalQurtState &s) {
  std::ostringstream oss;
  oss << "HALQURT ok=" << (s.ok ? 1 : 0) << " backend=" << s.backend;
  return oss.str();
}

} // namespace vrp
