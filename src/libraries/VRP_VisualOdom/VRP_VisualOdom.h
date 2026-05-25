#pragma once
/**
 * @module  libraries/VRP_VisualOdom
 * @dal     C
 * @req     VRP-LLRD-AP_VisualOdom
 * @parity  ArduPilot AP_VisualOdom — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct VisualOdomState {
  double vx_m_s{0.0};
  double vy_m_s{0.0};
  double quality{0.0};
  bool valid{false};
};

class VRP_VisualOdom {
public:
  bool init();
  VisualOdomState update(double dx_m, double dy_m, double dt_s);

private:
  double prev_q_{0.0};
};

std::string format_visual_odom(const VisualOdomState &s);

} // namespace vrp
