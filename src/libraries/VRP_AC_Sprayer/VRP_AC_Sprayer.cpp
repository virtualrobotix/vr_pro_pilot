#include "libraries/VRP_AC_Sprayer/VRP_AC_Sprayer.h"
#include <sstream>

namespace vrp {

bool VRP_AC_Sprayer::init() { return true; }

SprayerState VRP_AC_Sprayer::update(bool armed, float aux2) {
  SprayerState out{};
  out.pump_on = armed && aux2 > 0.0F;
  out.rate_l_min = out.pump_on ? 2.5F + aux2 * 3.0F : 0.0F;
  return out;
}

std::string format_sprayer(const SprayerState &s) {
  std::ostringstream oss;
  oss << "SPRAYER pump=" << (s.pump_on ? 1 : 0) << " rate=" << s.rate_l_min;
  return oss.str();
}

} // namespace vrp
