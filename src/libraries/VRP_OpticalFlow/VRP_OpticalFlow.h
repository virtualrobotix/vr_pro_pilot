#pragma once
/**
 * @module  libraries/VRP_OpticalFlow
 * @dal     C
 * @req     VRP-LLRD-AP_OpticalFlow
 * @parity  ArduPilot AP_OpticalFlow — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct OpticalFlowSample {
  double flow_x_rad_s{0.0};
  double flow_y_rad_s{0.0};
  double ground_distance_m{0.0};
  uint8_t quality{0};
  bool valid{false};
};

class VRP_OpticalFlow {
public:
  bool init();
  OpticalFlowSample update(double vx_m_s, double vy_m_s, double ground_m, uint64_t time_us);

private:
  double prev_vx_{0.0};
  double prev_vy_{0.0};
  bool have_prev_{false};
};

std::string format_optical_flow(const OpticalFlowSample &s);

} // namespace vrp
