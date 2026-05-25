#include "modules/nav_core/NavCore.h"

namespace vrp {

bool NavCore::init(const std::string &vehicle, double cruise_speed_m_s) {
  vehicle_ = vehicle;
  wpnav_.init(cruise_speed_m_s);
  l1_.init();
  last_ = WpNavOutput{};
  last_l1_ = L1Output{};
  return true;
}

WpNavOutput NavCore::update(const LocalPosition &pos, const Waypoint &target, const Waypoint &prev, bool use_l1,
                            bool active, UORB &uorb) {
  if (!active) {
    last_ = WpNavOutput{};
    last_l1_ = L1Output{};
    uorb.publish("nav/wp", "WPNAV idle");
    uorb.publish("nav/l1", "L1 idle");
    return last_;
  }

  if (use_l1 && vehicle_ == "vtol") {
    last_l1_ = l1_.update(pos, prev, target, 0.02);
    if (last_l1_.valid) {
      last_ = wpnav_.update(pos, target);
      last_.bearing_rad = last_l1_.nav_bearing_rad;
      uorb.publish("nav/l1", format_l1(last_l1_));
      uorb.publish("nav/wp", format_wpnav(last_));
      return last_;
    }
  }

  last_l1_ = L1Output{};
  last_ = wpnav_.update(pos, target);
  uorb.publish("nav/l1", "L1 bypass");
  uorb.publish("nav/wp", format_wpnav(last_));
  return last_;
}

} // namespace vrp
