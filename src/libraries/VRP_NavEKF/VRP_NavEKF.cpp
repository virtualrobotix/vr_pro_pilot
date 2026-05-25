#include "libraries/VRP_NavEKF/VRP_NavEKF.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_NavEKF::init() {
  seq_ = 0;
  return true;
}

NavEkfState VRP_NavEKF::update(const LocalPosition &pos, bool armed, uint64_t tick) {
  NavEkfState out{};
  out.valid = armed && pos.valid;
  out.states = out.valid ? 24 : 0;
  out.pos_err_m = out.valid ? std::sqrt(pos.x * pos.x + pos.y * pos.y) * 0.01 : 0.0;
  ++seq_;
  (void)tick;
  (void)seq_;
  return out;
}

std::string format_nav_ekf(const NavEkfState &s) {
  std::ostringstream oss;
  oss << "NAVEKF states=" << static_cast<int>(s.states) << " valid=" << (s.valid ? 1 : 0)
      << " err=" << s.pos_err_m;
  return oss.str();
}

} // namespace vrp
