#include "libraries/VRP_Beacon/VRP_Beacon.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Beacon::init() {
  bx_ = 10.0;
  by_ = -5.0;
  return true;
}

BeaconSample VRP_Beacon::update(double own_x_m, double own_y_m) {
  BeaconSample out{};
  const double dx = bx_ - own_x_m;
  const double dy = by_ - own_y_m;
  out.id = 7;
  out.distance_m = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  out.bearing_rad = std::atan2(dy, dx);
  out.valid = true;
  return out;
}

std::string format_beacon(const BeaconSample &s) {
  std::ostringstream oss;
  oss << "BEACON id=" << static_cast<int>(s.id) << " dist=" << s.distance_m << " brg=" << s.bearing_rad
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
