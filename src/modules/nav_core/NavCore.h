#pragma once

#include "libraries/VRP_AC_WPNav/VRP_AC_WPNav.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_L1_Control/VRP_L1_Control.h"
#include "middleware/uorb/UORB.h"

namespace vrp {

class NavCore {
public:
  bool init(const std::string &vehicle, double cruise_speed_m_s);
  WpNavOutput update(const LocalPosition &pos, const Waypoint &target, const Waypoint &prev, bool use_l1, bool active,
                     UORB &uorb);

  const WpNavOutput &last() const { return last_; }
  const L1Output &last_l1() const { return last_l1_; }

private:
  std::string vehicle_;
  VRP_AC_WPNav wpnav_{};
  VRP_L1_Control l1_{};
  WpNavOutput last_{};
  L1Output last_l1_{};
};

} // namespace vrp
