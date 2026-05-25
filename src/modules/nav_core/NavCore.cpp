#include "modules/nav_core/NavCore.h"

namespace vrp {

bool NavCore::init(const std::string &vehicle, double cruise_speed_m_s, double wp_radius_m) {
  vehicle_ = vehicle;
  wpnav_.init(cruise_speed_m_s, wp_radius_m, wp_radius_m * 2.5);
  if (is_ar_surface_vehicle(vehicle)) {
    ar_wpnav_.init(cruise_speed_m_s, wp_radius_m);
  }
  l1_.init();
  in_loiter_ = false;
  last_ = WpNavOutput{};
  last_l1_ = L1Output{};
  last_ar_ = ArWpNavOutput{};
  return true;
}

void NavCore::set_loiter_center(const Waypoint &center) {
  if (is_ar_surface_vehicle(vehicle_)) {
    ar_wpnav_.set_loiter_center(center);
  } else if (vehicle_ == "quad") {
    wpnav_.set_loiter_center(center);
  }
}

WpNavOutput NavCore::from_ar(const ArWpNavOutput &ar) {
  WpNavOutput out{};
  out.bearing_rad = ar.bearing_rad;
  out.distance_m = ar.distance_m;
  out.target_speed_m_s = ar.target_speed_m_s;
  out.turn_rate_rad_s = ar.turn_rate_rad_s;
  out.cross_track_m = ar.cross_track_m;
  out.wp_index = ar.wp_index;
  out.reached = ar.reached;
  out.valid = ar.valid;
  return out;
}

WpNavOutput NavCore::update(const LocalPosition &pos, const Attitude &attitude, const Waypoint &target,
                            const Waypoint &prev, bool use_l1, bool active, const std::string &mode, UORB &uorb) {
  if (is_ar_surface_vehicle(vehicle_)) {
    if (mode == "Loiter") {
      if (!in_loiter_) {
        ar_wpnav_.set_loiter_center(Waypoint{pos.x, pos.y, pos.z});
        in_loiter_ = true;
      }
    } else {
      in_loiter_ = false;
    }
    last_ar_ = ar_wpnav_.update(pos, attitude, target, prev, mode, active);
    last_ = from_ar(last_ar_);
    uorb.publish("nav/ar_wp", format_ar_wpnav(last_ar_));
    uorb.publish("nav/wp", format_wpnav(last_));
    uorb.publish("nav/l1", "L1 n/a boat");
    return last_;
  }

  if (vehicle_ == "quad") {
    if (mode == "Loiter" || mode == "AltHold") {
      if (!in_loiter_) {
        wpnav_.set_loiter_center(Waypoint{pos.x, pos.y, pos.z});
        in_loiter_ = true;
      }
    } else {
      in_loiter_ = false;
    }
    last_ = wpnav_.update(pos, attitude, target, prev, mode, active);
    uorb.publish("nav/ac_wp", format_ac_wpnav(last_));
    uorb.publish("nav/wp", format_wpnav(last_));
    uorb.publish("nav/l1", "L1 n/a quad");
    return last_;
  }

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
      last_ = wpnav_.update(pos, attitude, target, prev, mode, true);
      last_.bearing_rad = last_l1_.nav_bearing_rad;
      uorb.publish("nav/l1", format_l1(last_l1_));
      uorb.publish("nav/wp", format_wpnav(last_));
      return last_;
    }
  }

  last_l1_ = L1Output{};
  last_ = wpnav_.update(pos, attitude, target, prev, mode, active);
  uorb.publish("nav/l1", "L1 bypass");
  uorb.publish("nav/wp", format_wpnav(last_));
  return last_;
}

} // namespace vrp
