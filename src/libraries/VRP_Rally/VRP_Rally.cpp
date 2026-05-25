#include "libraries/VRP_Rally/VRP_Rally.h"

#include <cmath>
#include <limits>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Rally::init() {
  points_ = {{0.0, 0.0, 0.0F}, {30.0, 10.0, 5.0F}, {-15.0, 20.0, 3.0F}};
  return true;
}

RallyStatus VRP_Rally::nearest(const LocalPosition &pos) const {
  RallyStatus out{};
  if (points_.empty()) {
    return out;
  }
  double best = std::numeric_limits<double>::max();
  for (size_t i = 0; i < points_.size(); ++i) {
    const double dx = points_[i].x - pos.x;
    const double dy = points_[i].y - pos.y;
    const double d = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
    if (d < best) {
      best = d;
      out.nearest_index = i;
      out.distance_m = d;
      out.valid = true;
    }
  }
  return out;
}

Waypoint VRP_Rally::target_at(size_t index) const {
  if (index >= points_.size()) {
    return Waypoint{};
  }
  return Waypoint{points_[index].x, points_[index].y, static_cast<double>(points_[index].alt_m)};
}

std::string format_rally(const RallyStatus &s) {
  std::ostringstream oss;
  oss << "RALLY idx=" << s.nearest_index << " dist=" << s.distance_m << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
