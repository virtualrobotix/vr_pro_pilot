#include "libraries/VRP_AIS/VRP_AIS.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AIS::init() {
  base_x_ = 80.0;
  base_y_ = -20.0;
  return true;
}

AisVessel VRP_AIS::update(uint64_t tick, double own_x_m, double own_y_m) {
  AisVessel v{};
  const double t = static_cast<double>(tick) * 0.02;
  const double tx = base_x_ + std::cos(t * 0.09) * 12.0;
  const double ty = base_y_ + std::sin(t * 0.07) * 9.0;
  const double dx = tx - own_x_m;
  const double dy = ty - own_y_m;
  v.mmsi = 247001234;
  v.distance_m = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  v.cog_rad = std::atan2(dy, dx);
  v.sog_m_s = 2.5 + std::sin(t * 0.3) * 0.5;
  v.valid = true;
  return v;
}

std::string format_ais(const AisVessel &v) {
  std::ostringstream oss;
  oss << "AIS mmsi=" << v.mmsi << " dist=" << v.distance_m << " sog=" << v.sog_m_s
      << " valid=" << (v.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
