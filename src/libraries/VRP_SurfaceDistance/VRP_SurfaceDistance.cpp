#include "libraries/VRP_SurfaceDistance/VRP_SurfaceDistance.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_SurfaceDistance::init() {
  min_m_ = 0.05;
  return true;
}

SurfaceDistanceSample VRP_SurfaceDistance::update(const RangeFinderSample &rng, double pitch_rad) {
  SurfaceDistanceSample out{};
  if (!rng.valid) {
    return out;
  }
  const double tilt = std::cos(pitch_rad);
  out.agl_m = VRP_Math::clamp(rng.distance_m * std::max(0.2, tilt), min_m_, 200.0);
  out.valid = true;
  return out;
}

std::string format_surface_distance(const SurfaceDistanceSample &s) {
  std::ostringstream oss;
  oss << "SURFACE agl=" << s.agl_m << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
