#pragma once
/**
 * @module  libraries/VRP_AR_WPNav
 * @dal     B
 * @req     VRP-LLRD-AR_WPNav
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

struct ArWpNavOutput {
  double bearing_rad{0.0};
  double distance_m{0.0};
  double target_speed_m_s{0.0};
  double turn_rate_rad_s{0.0};
  double cross_track_m{0.0};
  uint16_t wp_index{0};
  bool active{false};
  bool reached{false};
  bool valid{false};
};

class VRP_AR_WPNav {
public:
  bool init(double cruise_speed_m_s, double wp_radius_m);
  void set_loiter_center(const Waypoint &center);
  ArWpNavOutput update(const LocalPosition &pos, const Attitude &attitude, const Waypoint &target,
                       const Waypoint &prev, const std::string &mode, bool active);

private:
  double cruise_speed_m_s_{2.0};
  double wp_radius_m_{2.0};
  Waypoint loiter_center_{};
  bool loiter_center_set_{false};
  uint16_t wp_index_{0};
};

std::string format_ar_wpnav(const ArWpNavOutput &o);

} // namespace vrp
