#include "libraries/VRP_AC_CustomControl/VRP_AC_CustomControl.h"
#include <sstream>

namespace vrp {

bool VRP_AC_CustomControl::init() { return true; }

CustomControlState VRP_AC_CustomControl::update(bool armed, float roll, float pitch) {
  CustomControlState out{};
  out.active = armed;
  out.roll = roll;
  out.pitch = pitch;
  return out;
}

std::string format_custom_control(const CustomControlState &s) {
  std::ostringstream oss;
  oss << "CUSTCTL active=" << (s.active ? 1 : 0) << " roll=" << s.roll << " pitch=" << s.pitch;
  return oss.str();
}

} // namespace vrp
