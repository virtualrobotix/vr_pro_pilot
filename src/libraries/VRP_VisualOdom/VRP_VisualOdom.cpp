#include "libraries/VRP_VisualOdom/VRP_VisualOdom.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_VisualOdom::init() {
  prev_q_ = 0.0;
  return true;
}

VisualOdomState VRP_VisualOdom::update(double dx_m, double dy_m, double dt_s) {
  VisualOdomState out{};
  if (dt_s > 0.0) {
    out.vx_m_s = dx_m / dt_s;
    out.vy_m_s = dy_m / dt_s;
    out.quality = std::min(1.0, std::sqrt(out.vx_m_s * out.vx_m_s + out.vy_m_s * out.vy_m_s) / 5.0);
    out.valid = out.quality > 0.01;
  }
  prev_q_ = out.quality;
  return out;
}

std::string format_visual_odom(const VisualOdomState &s) {
  std::ostringstream oss;
  oss << "VISO vx=" << s.vx_m_s << " vy=" << s.vy_m_s << " q=" << s.quality << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
