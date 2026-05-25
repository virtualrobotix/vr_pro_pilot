#include "libraries/VRP_RangeFinder/VRP_RangeFinder.h"

#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_RangeFinder::init(double ground_z_m, double max_range_m) {
  ground_z_m_ = ground_z_m;
  max_range_m_ = max_range_m;
  return true;
}

RangeFinderSample VRP_RangeFinder::update(double vehicle_z_m, uint64_t time_us) {
  RangeFinderSample out{};
  out.min_m = 0.01;
  out.max_m = max_range_m_;
  out.time_us = time_us;
  const double height_agl = ground_z_m_ - vehicle_z_m;
  if (height_agl >= out.min_m && height_agl <= out.max_m) {
    out.distance_m = height_agl;
    out.valid = true;
  }
  return out;
}

std::string format_rangefinder(const RangeFinderSample &s) {
  std::ostringstream oss;
  oss << "RANGEFINDER dist=" << s.distance_m << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
