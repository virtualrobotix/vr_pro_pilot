#include "libraries/VRP_AC_WPNav/VRP_AC_WPNav.h"

#include <cmath>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AC_WPNav::init(double cruise_speed_m_s) {
  cruise_speed_m_s_ = cruise_speed_m_s;
  return true;
}

WpNavOutput VRP_AC_WPNav::update(const LocalPosition &pos, const Waypoint &target) {
  WpNavOutput out{};
  if (!pos.valid) {
    return out;
  }
  const double dx = target.x - pos.x;
  const double dy = target.y - pos.y;
  out.distance_m = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  out.bearing_rad = std::atan2(dy, dx);
  out.alt_error_m = target.z - pos.z;
  out.target_speed_m_s = VRP_Math::clamp(cruise_speed_m_s_, 0.5, 8.0);
  out.valid = true;
  return out;
}

} // namespace vrp
