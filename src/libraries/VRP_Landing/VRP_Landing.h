#pragma once
/**
 * @module  libraries/VRP_Landing
 * @dal     B
 * @req     VRP-LLRD-AP_Landing
 * @parity  ArduPilot AP_Landing — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_RangeFinder/VRP_RangeFinder.h"

namespace vrp {

struct LandingSetpoint {
  double target_z_m{0.0};
  float throttle{0.55F};
  bool complete{false};
  bool land_detector{false};
  bool request_disarm{false};
  std::string phase{"idle"};
};

class VRP_Landing {
public:
  bool init(double flare_alt_m = 2.0, double land_alt_m = 0.3);
  LandingSetpoint update(const LocalPosition &pos, const RangeFinderSample &rng, double dt_s);
  void reset();

private:
  double flare_alt_m_{2.0};
  double land_alt_m_{0.3};
  std::string phase_{"idle"};
  int bounce_count_{0};
  double last_agl_{999.0};
};

std::string format_landing(const LandingSetpoint &sp);

} // namespace vrp
