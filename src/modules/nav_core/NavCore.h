#pragma once

#include "libraries/VRP_AC_WPNav/VRP_AC_WPNav.h"
#include "libraries/VRP_AR_WPNav/VRP_AR_WPNav.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_L1_Control/VRP_L1_Control.h"
#include "middleware/uorb/UORB.h"

namespace vrp {

class NavCore {
public:
  bool init(const std::string &vehicle, double cruise_speed_m_s, double wp_radius_m = 2.0);
  void set_loiter_center(const Waypoint &center);
  WpNavOutput update(const LocalPosition &pos, const Attitude &attitude, const Waypoint &target,
                     const Waypoint &prev, bool use_l1, bool active, const std::string &mode, UORB &uorb);

  const WpNavOutput &last() const { return last_; }
  const L1Output &last_l1() const { return last_l1_; }
  const ArWpNavOutput &last_ar() const { return last_ar_; }

private:
  static WpNavOutput from_ar(const ArWpNavOutput &ar);

  std::string vehicle_;
  VRP_AC_WPNav wpnav_{};
  VRP_AR_WPNav ar_wpnav_{};
  VRP_L1_Control l1_{};
  WpNavOutput last_{};
  L1Output last_l1_{};
  ArWpNavOutput last_ar_{};
  bool in_loiter_{false};
};

} // namespace vrp
