#pragma once
/**
 * @module  libraries/VRP_InertialNav
 * @dal     B
 * @req     VRP-LLRD-AP_InertialNav
 * @parity  ArduPilot AP_InertialNav — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct LocalPosition;

struct InertialNavState {
  double vx_m_s{0.0};
  double vy_m_s{0.0};
  bool valid{false};
};

class VRP_InertialNav {
public:
  bool init();
  InertialNavState update(const LocalPosition &pos, bool armed);

private:
  double prev_x_{0.0};
  double prev_y_{0.0};
  bool have_prev_{false};
};

std::string format_inertial_nav(const InertialNavState &s);

} // namespace vrp
