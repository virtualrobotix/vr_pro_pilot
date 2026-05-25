#pragma once
/**
 * @module  libraries/VRP_NavEKF
 * @dal     B
 * @req     VRP-LLRD-AP_NavEKF
 * @parity  ArduPilot AP_NavEKF — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct LocalPosition;

struct NavEkfState {
  uint8_t states{0};
  bool valid{false};
  double pos_err_m{0.0};
};

class VRP_NavEKF {
public:
  bool init();
  NavEkfState update(const LocalPosition &pos, bool armed, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_nav_ekf(const NavEkfState &s);

} // namespace vrp
