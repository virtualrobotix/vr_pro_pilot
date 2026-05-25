#include "libraries/VRP_AR_WPNav/VRP_AR_WPNav.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_AR_WPNav::init() {
  wp_ = 0;
  return true;
}

ArWpNavState VRP_AR_WPNav::update(const std::string &mode, const LocalPosition &pos, uint64_t tick) {
  ArWpNavState out{};
  out.active = (mode == "Auto" || mode == "Manual");
  if (out.active) {
    wp_ = static_cast<uint16_t>((tick / 2) % 5);
  }
  out.wp_index = wp_;
  const double dx = 50.0 - pos.x;
  const double dy = 0.0 - pos.y;
  out.dist_m = std::sqrt(dx * dx + dy * dy);
  return out;
}

std::string format_ar_wpnav(const ArWpNavState &s) {
  std::ostringstream oss;
  oss << "ARWPNAV active=" << (s.active ? 1 : 0) << " wp=" << s.wp_index << " dist=" << static_cast<int>(s.dist_m);
  return oss.str();
}

} // namespace vrp
