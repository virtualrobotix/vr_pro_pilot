#include "libraries/VRP_Proximity/VRP_Proximity.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Proximity::init(double warn_m, double fence_radius_m) {
  warn_m_ = warn_m;
  fence_radius_m_ = fence_radius_m;
  return true;
}

ProximitySample VRP_Proximity::update(double x_m, double y_m, const RangeFinderSample &rng, const AdsbVehicle *adsb) {
  ProximitySample out{};
  out.min_distance_m = fence_radius_m_;
  out.angle_rad = std::atan2(y_m, x_m);

  if (rng.valid) {
    out.min_distance_m = VRP_Math::clamp(rng.distance_m, 0.0, out.min_distance_m);
    out.angle_rad = 0.0;
  }

  if (adsb != nullptr && adsb->valid && adsb->distance_m < out.min_distance_m) {
    out.min_distance_m = adsb->distance_m;
    out.angle_rad = std::atan2(adsb->lat_e7 * 1e-7 - 45.0, adsb->lon_e7 * 1e-7 - 9.0);
  }

  const double radial = std::sqrt(VRP_Math::sq(x_m) + VRP_Math::sq(y_m));
  const double boundary = fence_radius_m_ - radial;
  if (boundary < out.min_distance_m) {
    out.min_distance_m = boundary;
    out.angle_rad = std::atan2(-y_m, -x_m);
  }

  out.valid = true;
  out.breach = out.min_distance_m < warn_m_;
  return out;
}

std::string format_proximity(const ProximitySample &s) {
  std::ostringstream oss;
  oss << "PROXIMITY min=" << s.min_distance_m << " breach=" << (s.breach ? 1 : 0)
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
