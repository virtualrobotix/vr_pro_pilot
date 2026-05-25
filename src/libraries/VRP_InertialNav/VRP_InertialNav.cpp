#include "libraries/VRP_InertialNav/VRP_InertialNav.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <sstream>

namespace vrp {

bool VRP_InertialNav::init() {
  prev_x_ = 0.0;
  prev_y_ = 0.0;
  have_prev_ = false;
  return true;
}

InertialNavState VRP_InertialNav::update(const LocalPosition &pos, bool armed) {
  InertialNavState out{};
  out.valid = armed && pos.valid;
  if (have_prev_) {
    out.vx_m_s = (pos.x - prev_x_) / 0.02;
    out.vy_m_s = (pos.y - prev_y_) / 0.02;
  } else if (pos.valid) {
    out.vx_m_s = pos.vx;
    out.vy_m_s = pos.vy;
  }
  prev_x_ = pos.x;
  prev_y_ = pos.y;
  have_prev_ = true;
  return out;
}

std::string format_inertial_nav(const InertialNavState &s) {
  std::ostringstream oss;
  oss << "INERTNAV vx=" << s.vx_m_s << " vy=" << s.vy_m_s << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
