#include "libraries/VRP_Navigation/VRP_Navigation.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_Navigation::init() {
  seq_ = 0;
  return true;
}

NavigationState VRP_Navigation::update(const std::string &mode, const LocalPosition &pos, double target_x,
                                       double target_y) {
  NavigationState out{};
  out.mode = mode;
  out.active = (mode == "Auto" || mode == "RTL" || mode == "Loiter");
  const double dx = target_x - pos.x;
  const double dy = target_y - pos.y;
  out.dist_m = std::sqrt(dx * dx + dy * dy);
  out.bearing_deg = std::atan2(dy, dx) * 180.0 / 3.141592653589793;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_navigation(const NavigationState &s) {
  std::ostringstream oss;
  oss << "NAV mode=" << s.mode << " active=" << (s.active ? 1 : 0) << " dist=" << static_cast<int>(s.dist_m)
      << " brg=" << static_cast<int>(s.bearing_deg);
  return oss.str();
}

} // namespace vrp
