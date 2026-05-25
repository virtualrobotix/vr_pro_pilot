#pragma once
/**
 * @module  libraries/VRP_Follow
 * @dal     C
 * @req     VRP-LLRD-AP_Follow
 * @parity  ArduPilot AP_Follow — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct FollowState {
  bool active{false};
  double dist_m{0.0};
  double bearing_deg{0.0};
};

class VRP_Follow {
public:
  bool init();
  FollowState update(const std::string &mode, double target_x, double target_y, double pos_x, double pos_y);

private:
  double target_x_{100.0};
  double target_y_{0.0};
};

std::string format_follow(const FollowState &s);

} // namespace vrp
