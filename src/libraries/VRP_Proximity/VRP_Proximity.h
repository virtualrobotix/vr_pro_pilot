#pragma once
/**
 * @module  libraries/VRP_Proximity
 * @dal     C
 * @req     VRP-LLRD-AP_Proximity
 * @parity  ArduPilot AP_Proximity — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_RangeFinder/VRP_RangeFinder.h"
#include "libraries/VRP_ADSB/VRP_ADSB.h"

namespace vrp {

struct ProximitySample {
  double min_distance_m{999.0};
  double angle_rad{0.0};
  bool valid{false};
  bool breach{false};
};

class VRP_Proximity {
public:
  bool init(double warn_m = 3.0, double fence_radius_m = 25.0);
  ProximitySample update(double x_m, double y_m, const RangeFinderSample &rng, const AdsbVehicle *adsb = nullptr);

private:
  double warn_m_{3.0};
  double fence_radius_m_{25.0};
};

std::string format_proximity(const ProximitySample &s);

} // namespace vrp
