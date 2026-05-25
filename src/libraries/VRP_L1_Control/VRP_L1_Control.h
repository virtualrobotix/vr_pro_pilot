#pragma once
/**
 * @module  libraries/VRP_L1_Control
 * @dal     B
 * @req     VRP-LLRD-AP_L1_Control
 * @parity  ArduPilot AP_L1_Control — clean-room BSD rewrite
 * @status  partial
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

struct L1Output {
  double bearing_rad{0.0};
  double nav_bearing_rad{0.0};
  double distance_m{0.0};
  bool valid{false};
};

class VRP_L1_Control {
public:
  bool init(double period_s = 25.0, double damping = 0.75);
  L1Output update(const LocalPosition &pos, const Waypoint &from, const Waypoint &to, double dt_s);

private:
  double period_s_{25.0};
  double damping_{0.75};
};

std::string format_l1(const L1Output &out);

} // namespace vrp
