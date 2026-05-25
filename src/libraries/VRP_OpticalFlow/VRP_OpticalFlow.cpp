#include "libraries/VRP_OpticalFlow/VRP_OpticalFlow.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_OpticalFlow::init() {
  have_prev_ = false;
  return true;
}

OpticalFlowSample VRP_OpticalFlow::update(double vx_m_s, double vy_m_s, double ground_m, uint64_t time_us) {
  (void)time_us;
  OpticalFlowSample out{};
  out.ground_distance_m = std::max(0.05, ground_m);
  if (have_prev_ && out.ground_distance_m > 0.05) {
    out.flow_x_rad_s = (vx_m_s - prev_vx_) / out.ground_distance_m;
    out.flow_y_rad_s = (vy_m_s - prev_vy_) / out.ground_distance_m;
    out.quality = 200;
    out.valid = true;
  } else {
    out.flow_x_rad_s = vx_m_s / out.ground_distance_m;
    out.flow_y_rad_s = vy_m_s / out.ground_distance_m;
    out.quality = 180;
    out.valid = true;
  }
  prev_vx_ = vx_m_s;
  prev_vy_ = vy_m_s;
  have_prev_ = true;
  return out;
}

std::string format_optical_flow(const OpticalFlowSample &s) {
  std::ostringstream oss;
  oss << "FLOW fx=" << s.flow_x_rad_s << " fy=" << s.flow_y_rad_s << " dist=" << s.ground_distance_m
      << " q=" << static_cast<int>(s.quality) << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
