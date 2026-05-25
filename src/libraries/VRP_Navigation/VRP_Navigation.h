#pragma once
/**
 * @module  libraries/VRP_Navigation
 * @dal     C
 * @req     VRP-LLRD-AP_Navigation
 * @parity  ArduPilot AP_Navigation — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct LocalPosition;

struct NavigationState {
  std::string mode{"idle"};
  double dist_m{0.0};
  double bearing_deg{0.0};
  bool active{false};
};

class VRP_Navigation {
public:
  bool init();
  NavigationState update(const std::string &mode, const LocalPosition &pos, double target_x, double target_y);

private:
  uint32_t seq_{0};
};

std::string format_navigation(const NavigationState &s);

} // namespace vrp
