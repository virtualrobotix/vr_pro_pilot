#include "libraries/VRP_L1_Control/VRP_L1_Control.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_L1_Control::init(double period_s, double damping) {
  period_s_ = period_s;
  damping_ = damping;
  return true;
}

L1Output VRP_L1_Control::update(const LocalPosition &pos, const Waypoint &from, const Waypoint &to, double dt_s) {
  (void)dt_s;
  L1Output out{};
  if (!pos.valid) {
    return out;
  }

  const double abx = to.x - from.x;
  const double aby = to.y - from.y;
  const double track_len = std::sqrt(VRP_Math::sq(abx) + VRP_Math::sq(aby));
  if (track_len < 0.5) {
    const double dx = to.x - pos.x;
    const double dy = to.y - pos.y;
    out.distance_m = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
    out.bearing_rad = std::atan2(dy, dx);
    out.nav_bearing_rad = out.bearing_rad;
    out.valid = true;
    return out;
  }

  const double speed = VRP_Math::clamp(std::sqrt(VRP_Math::sq(pos.vx) + VRP_Math::sq(pos.vy)), 3.0, 25.0);
  const double l1_dist = VRP_Math::clamp(period_s_ * damping_ * speed * 0.04, 5.0, 80.0);

  const double apx = pos.x - from.x;
  const double apy = pos.y - from.y;
  const double t = VRP_Math::clamp((apx * abx + apy * aby) / (track_len * track_len), 0.0, 1.0);
  const double px = from.x + abx * t;
  const double py = from.y + aby * t;

  const double dx = to.x - px;
  const double dy = to.y - py;
  const double seg_dist = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  const double scale = seg_dist > 1e-3 ? l1_dist / seg_dist : 0.0;
  const double l1x = px + dx * scale;
  const double l1y = py + dy * scale;

  const double nav_dx = l1x - pos.x;
  const double nav_dy = l1y - pos.y;
  out.distance_m = std::sqrt(VRP_Math::sq(nav_dx) + VRP_Math::sq(nav_dy));
  out.nav_bearing_rad = std::atan2(nav_dy, nav_dx);
  out.bearing_rad = std::atan2(to.y - pos.y, to.x - pos.x);
  out.valid = true;
  return out;
}

std::string format_l1(const L1Output &out) {
  std::ostringstream oss;
  oss << "L1 brg=" << out.bearing_rad << " nav_brg=" << out.nav_bearing_rad << " dist=" << out.distance_m
      << " valid=" << (out.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
