#pragma once
/**
 * @module  libraries/VRP_RangeFinder
 * @dal     C
 * @req     VRP-LLRD-AP_RangeFinder
 * @parity  ArduPilot AP_RangeFinder — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RangeFinderSample {
  double distance_m{0.0};
  double min_m{0.2};
  double max_m{30.0};
  bool valid{false};
  uint64_t time_us{0};
};

class VRP_RangeFinder {
public:
  bool init(double ground_z_m = 0.0, double max_range_m = 30.0);
  RangeFinderSample update(double vehicle_z_m, uint64_t time_us);

private:
  double ground_z_m_{0.0};
  double max_range_m_{30.0};
};

std::string format_rangefinder(const RangeFinderSample &s);

} // namespace vrp
