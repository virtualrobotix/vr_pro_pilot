#include "libraries/VRP_AR_WPNav/VRP_AR_WPNav.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AR_WPNav::init(double cruise_speed_m_s, double wp_radius_m) {
  cruise_speed_m_s_ = VRP_Math::clamp(cruise_speed_m_s, 0.2, 15.0);
  wp_radius_m_ = VRP_Math::clamp(wp_radius_m, 0.5, 50.0);
  wp_index_ = 0;
  loiter_center_set_ = false;
  return true;
}

void VRP_AR_WPNav::set_loiter_center(const Waypoint &center) {
  loiter_center_ = center;
  loiter_center_set_ = true;
}

ArWpNavOutput VRP_AR_WPNav::update(const LocalPosition &pos, const Attitude &attitude, const Waypoint &target,
                                   const Waypoint &prev, const std::string &mode, bool active) {
  ArWpNavOutput out{};
  out.active = active && mode != "Manual" && mode != "Disarmed";
  if (!out.active || !pos.valid) {
    return out;
  }

  Waypoint nav_target = target;
  if (mode == "Loiter" && loiter_center_set_) {
    nav_target = loiter_center_;
  } else if (mode == "RTL") {
    nav_target = Waypoint{0.0, 0.0, 0.0};
  }

  const double dx = nav_target.x - pos.x;
  const double dy = nav_target.y - pos.y;
  out.distance_m = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  out.bearing_rad = std::atan2(dy, dx);
  out.wp_index = wp_index_;

  if (prev.x != 0.0 || prev.y != 0.0 || target.x != 0.0 || target.y != 0.0) {
    const double seg_dx = nav_target.x - prev.x;
    const double seg_dy = nav_target.y - prev.y;
    const double seg_len = std::sqrt(VRP_Math::sq(seg_dx) + VRP_Math::sq(seg_dy));
    if (seg_len > 0.1) {
      out.cross_track_m =
          ((pos.x - prev.x) * seg_dy - (pos.y - prev.y) * seg_dx) / seg_len;
    }
  }

  const double heading = attitude.yaw_rad;
  double bearing_error = VRP_Math::wrap_pi(out.bearing_rad - heading);
  out.turn_rate_rad_s = VRP_Math::clamp(bearing_error * 1.5 - out.cross_track_m * 0.4, -1.2, 1.2);

  if (out.distance_m <= wp_radius_m_) {
    out.reached = true;
    if (mode == "Loiter") {
      out.target_speed_m_s = VRP_Math::clamp(out.distance_m * 0.5, 0.0, 0.5);
      out.turn_rate_rad_s = VRP_Math::clamp(bearing_error * 0.8, -0.4, 0.4);
    } else {
      out.target_speed_m_s = 0.0;
      out.turn_rate_rad_s = 0.0;
    }
  } else {
    out.reached = false;
    const double speed_scale = VRP_Math::clamp(out.distance_m / 10.0, 0.35, 1.0);
    out.target_speed_m_s = cruise_speed_m_s_ * speed_scale;
  }

  out.valid = true;
  return out;
}

std::string format_ar_wpnav(const ArWpNavOutput &o) {
  std::ostringstream oss;
  oss << "ARWPNAV active=" << (o.active ? 1 : 0) << " wp=" << o.wp_index << " dist=" << static_cast<int>(o.distance_m)
      << " spd=" << o.target_speed_m_s << " trn=" << o.turn_rate_rad_s << " xtrack=" << o.cross_track_m
      << " reached=" << (o.reached ? 1 : 0);
  return oss.str();
}

} // namespace vrp
