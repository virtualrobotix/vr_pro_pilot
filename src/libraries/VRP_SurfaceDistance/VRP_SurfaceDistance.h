#pragma once
/**
 * @module  libraries/VRP_SurfaceDistance
 * @dal     C
 * @req     VRP-LLRD-AP_SurfaceDistance
 * @parity  ArduPilot AP_SurfaceDistance — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

#include "libraries/VRP_RangeFinder/VRP_RangeFinder.h"

namespace vrp {

struct SurfaceDistanceSample {
  double agl_m{0.0};
  bool valid{false};
};

class VRP_SurfaceDistance {
public:
  bool init();
  SurfaceDistanceSample update(const RangeFinderSample &rng, double pitch_rad);

private:
  double min_m_{0.05};
};

std::string format_surface_distance(const SurfaceDistanceSample &s);

} // namespace vrp
