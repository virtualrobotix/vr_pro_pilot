#pragma once
/**
 * @module  libraries/VRP_SmartRTL
 * @dal     B
 * @req     VRP-LLRD-AP_SmartRTL
 * @parity  ArduPilot AP_SmartRTL — clean-room BSD rewrite
 * @status  partial
 */
#include <cstddef>
#include <string>
#include <vector>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

struct SmartRtlState {
  Waypoint target{};
  bool active{false};
  bool complete{false};
  size_t path_points{0};
  size_t rtl_index{0};
};

class VRP_SmartRTL {
public:
  bool init(size_t max_points = 64, double min_step_m = 1.0);
  void update(const LocalPosition &pos, bool armed);
  SmartRtlState activate();
  SmartRtlState update_rtl(const LocalPosition &pos, double acceptance_radius_m = 2.0);
  void clear();
  std::string status() const;

private:
  std::vector<Waypoint> path_{};
  size_t max_points_{64};
  double min_step_m_{1.0};
  bool rtl_active_{false};
  size_t rtl_index_{0};
  bool has_last_{false};
  Waypoint last_recorded_{};
};

std::string format_smart_rtl(const SmartRtlState &state);

} // namespace vrp
