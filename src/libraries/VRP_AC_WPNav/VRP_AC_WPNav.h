#pragma once
/**
 * @module  libraries/VRP_AC_WPNav
 * @dal     B
 * @req     VRP-LLRD-AC_WPNav
 * @parity  ArduPilot AC_WPNav
 * @status  partial
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_AC_WPNav {
public:
  bool init(double cruise_speed_m_s, double wp_radius_m = 2.0, double loiter_radius_m = 5.0);
  void set_loiter_center(const Waypoint &center);
  WpNavOutput update(const LocalPosition &pos, const Attitude &attitude, const Waypoint &target,
                     const Waypoint &prev, const std::string &mode, bool active);

private:
  double cruise_speed_m_s_{2.0};
  double wp_radius_m_{2.0};
  double loiter_radius_m_{5.0};
  Waypoint loiter_center_{};
  bool loiter_center_set_{false};
  uint16_t wp_index_{0};
  double last_speed_m_s_{0.0};
  double max_accel_m_s2_{2.5};
};

std::string format_ac_wpnav(const WpNavOutput &o);

} // namespace vrp
