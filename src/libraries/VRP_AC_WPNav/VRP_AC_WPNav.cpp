#include "libraries/VRP_AC_WPNav/VRP_AC_WPNav.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AC_WPNav::init(double cruise_speed_m_s, double wp_radius_m, double loiter_radius_m) {
  cruise_speed_m_s_ = VRP_Math::clamp(cruise_speed_m_s, 0.5, 12.0);
  wp_radius_m_ = VRP_Math::clamp(wp_radius_m, 0.5, 30.0);
  loiter_radius_m_ = VRP_Math::clamp(loiter_radius_m, 1.0, 100.0);
  loiter_center_set_ = false;
  wp_index_ = 0;
  last_speed_m_s_ = 0.0;
  return true;
}

void VRP_AC_WPNav::set_loiter_center(const Waypoint &center) {
  loiter_center_ = center;
  loiter_center_set_ = true;
}

WpNavOutput VRP_AC_WPNav::update(const LocalPosition &pos, const Attitude &attitude, const Waypoint &target,
                                 const Waypoint &prev, const std::string &mode, bool active) {
  WpNavOutput out{};
  if (!active || !pos.valid || mode == "Disarmed" || mode == "Manual" || mode == "Stabilize" || mode == "Acro") {
    return out;
  }

  Waypoint nav_target = target;
  if (mode == "Loiter" && loiter_center_set_) {
    nav_target = loiter_center_;
  } else if (mode == "RTL" || mode == "SmartRTL") {
    nav_target = Waypoint{0.0, 0.0, 0.0};
  }

  const double dx = nav_target.x - pos.x;
  const double dy = nav_target.y - pos.y;
  out.distance_m = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  out.bearing_rad = std::atan2(dy, dx);
  out.alt_error_m = nav_target.z - pos.z;
  out.wp_index = wp_index_;

  if (prev.x != 0.0 || prev.y != 0.0 || nav_target.x != 0.0 || nav_target.y != 0.0) {
    const double seg_dx = nav_target.x - prev.x;
    const double seg_dy = nav_target.y - prev.y;
    const double seg_len = std::sqrt(VRP_Math::sq(seg_dx) + VRP_Math::sq(seg_dy));
    if (seg_len > 0.1) {
      out.cross_track_m = ((pos.x - prev.x) * seg_dy - (pos.y - prev.y) * seg_dx) / seg_len;
    }
  }

  const double bearing_error = VRP_Math::wrap_pi(out.bearing_rad - attitude.yaw_rad);
  out.turn_rate_rad_s = VRP_Math::clamp(bearing_error * 1.2 - out.cross_track_m * 0.35, -1.5, 1.5);

  const double accept_radius = mode == "Loiter" ? loiter_radius_m_ : wp_radius_m_;
  if (out.distance_m <= accept_radius) {
    out.reached = true;
    if (mode == "Loiter") {
      out.target_speed_m_s = VRP_Math::clamp(out.distance_m * 0.4, 0.0, 0.6);
      out.turn_rate_rad_s = VRP_Math::clamp(bearing_error * 0.6, -0.35, 0.35);
    } else {
      out.target_speed_m_s = 0.0;
      out.turn_rate_rad_s = 0.0;
    }
  } else {
    out.reached = false;
    const double speed_scale = VRP_Math::clamp(out.distance_m / 12.0, 0.3, 1.0);
    const double target = cruise_speed_m_s_ * speed_scale;
    const double delta = target - last_speed_m_s_;
    last_speed_m_s_ += VRP_Math::clamp(delta, -max_accel_m_s2_ * 0.02, max_accel_m_s2_ * 0.02);
    out.target_speed_m_s = last_speed_m_s_;
  }

  out.valid = true;
  return out;
}

std::string format_ac_wpnav(const WpNavOutput &o) {
  std::ostringstream oss;
  oss << "ACWPNAV active=" << (o.valid ? 1 : 0) << " wp=" << o.wp_index << " dist=" << static_cast<int>(o.distance_m)
      << " spd=" << o.target_speed_m_s << " trn=" << o.turn_rate_rad_s << " xtrack=" << o.cross_track_m
      << " alt_err=" << o.alt_error_m << " reached=" << (o.reached ? 1 : 0) << " scurve=1";
  return oss.str();
}

} // namespace vrp
