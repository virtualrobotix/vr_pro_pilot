#include "libraries/VRP_AC_Autorotation/VRP_AC_Autorotation.h"

#include <sstream>

namespace vrp {

bool VRP_AC_Autorotation::init() {
  seq_ = 0;
  return true;
}

AutorotationState VRP_AC_Autorotation::update(bool armed, bool rtl_active, float throttle) {
  AutorotationState out{};
  out.active = armed && rtl_active;
  out.phase = out.active ? 2 : 0;
  out.rpm = out.active ? static_cast<uint16_t>(800.0F + throttle * 2000.0F) : 0;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_autorotation(const AutorotationState &s) {
  std::ostringstream oss;
  oss << "AUTOROT active=" << (s.active ? 1 : 0) << " phase=" << static_cast<int>(s.phase) << " rpm=" << s.rpm;
  return oss.str();
}

} // namespace vrp
