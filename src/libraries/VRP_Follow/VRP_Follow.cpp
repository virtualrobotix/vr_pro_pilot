#include "libraries/VRP_Follow/VRP_Follow.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_Follow::init() {
  target_x_ = 100.0;
  target_y_ = 0.0;
  return true;
}

FollowState VRP_Follow::update(const std::string &mode, double target_x, double target_y, double pos_x,
                               double pos_y) {
  FollowState out{};
  out.active = (mode == "FOLLOW" || mode == "Auto" || mode == "Loiter");
  if (out.active) {
    target_x_ = target_x;
    target_y_ = target_y;
  }
  const double dx = target_x_ - pos_x;
  const double dy = target_y_ - pos_y;
  out.dist_m = std::sqrt(dx * dx + dy * dy);
  out.bearing_deg = std::atan2(dy, dx) * 180.0 / 3.141592653589793;
  return out;
}

std::string format_follow(const FollowState &s) {
  std::ostringstream oss;
  oss << "FOLLOW active=" << (s.active ? 1 : 0) << " dist_m=" << static_cast<int>(s.dist_m)
      << " brg=" << static_cast<int>(s.bearing_deg);
  return oss.str();
}

} // namespace vrp
