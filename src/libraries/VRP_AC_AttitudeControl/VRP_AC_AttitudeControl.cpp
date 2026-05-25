#include "libraries/VRP_AC_AttitudeControl/VRP_AC_AttitudeControl.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AC_AttitudeControl::init(double max_tilt_deg) {
  max_tilt_rad_ = VRP_Math::deg_to_rad(VRP_Math::clamp(max_tilt_deg, 10.0, 60.0));
  roll_pid_.reset();
  pitch_pid_.reset();
  yaw_pid_.reset();
  alt_pid_.reset();
  tune_scale_ = 1.0F;
  last_vx_ = 0.0;
  last_vy_ = 0.0;
  last_target_speed_ = 0.0;
  return true;
}

void VRP_AC_AttitudeControl::apply_autotune_scale(float scale) {
  tune_scale_ = VRP_Math::clamp(scale, 0.5F, 2.0F);
}

ControlTorque VRP_AC_AttitudeControl::update(const Attitude &attitude, const AttitudeSetpoint &sp, double dt_s) {
  ControlTorque out{};
  const float scale = tune_scale_;
  out.roll = static_cast<float>(
      VRP_Math::clamp(roll_pid_.update(sp.roll_rad, attitude.roll_rad, dt_s) * scale, -1.0, 1.0));
  out.pitch = static_cast<float>(
      VRP_Math::clamp(pitch_pid_.update(sp.pitch_rad, attitude.pitch_rad, dt_s) * scale, -1.0, 1.0));

  if (sp.acro_rate) {
    out.yaw = static_cast<float>(VRP_Math::clamp(sp.yaw_rate_rad_s * 0.8 * scale, -1.0, 1.0));
  } else if (sp.heading_hold) {
    const double yaw_err = VRP_Math::wrap_pi(sp.yaw_target_rad - attitude.yaw_rad);
    out.yaw = static_cast<float>(
        VRP_Math::clamp(yaw_pid_.update(0.0, -yaw_err, dt_s) * scale + sp.yaw_rate_rad_s * 0.35, -1.0, 1.0));
  } else {
    out.yaw = static_cast<float>(
        VRP_Math::clamp(sp.yaw_rate_rad_s * 0.5 * static_cast<double>(scale), -1.0, 1.0));
  }
  return out;
}

PosControlSetpoint VRP_AC_AttitudeControl::update_pos(const LocalPosition &pos, const WpNavOutput &nav,
                                                      double target_z_m, double max_tilt_rad, bool alt_hold) {
  PosControlSetpoint out{};
  const double tilt = max_tilt_rad > 0.0 ? max_tilt_rad : max_tilt_rad_;

  if (nav.valid) {
    const double speed_cmd = nav.target_speed_m_s;
    const double speed_accel = (speed_cmd - last_target_speed_) / 0.02;
    last_target_speed_ = VRP_Math::clamp(last_target_speed_ + VRP_Math::clamp(speed_accel, -2.0, 2.0) * 0.02, 0.0,
                                         speed_cmd);
    const double lean = VRP_Math::clamp(last_target_speed_ / 6.0 * tilt, 0.0, tilt);
    const double ff_x = std::cos(nav.bearing_rad) * last_target_speed_ * 0.04;
    const double ff_y = std::sin(nav.bearing_rad) * last_target_speed_ * 0.04;
    out.pitch_rad = std::cos(nav.bearing_rad) * lean - nav.cross_track_m * 0.04 + ff_x;
    out.roll_rad = std::sin(nav.bearing_rad) * lean + nav.cross_track_m * 0.02 + ff_y;
    out.yaw_rate_rad_s = nav.turn_rate_rad_s;
  }

  if (alt_hold) {
    out.thrust_base = static_cast<float>(VRP_Math::clamp(hover_throttle_ + alt_pid_.update(target_z_m, pos.z, 0.02),
                                                         0.35, 0.9));
    const double ax_j = (pos.vx - last_vx_) / 0.02;
    const double ay_j = (pos.vy - last_vy_) / 0.02;
    last_vx_ = pos.vx;
    last_vy_ = pos.vy;
    out.pitch_rad = VRP_Math::clamp(out.pitch_rad - pos.vx * 0.08 - VRP_Math::clamp(ax_j, -3.0, 3.0) * 0.02, -tilt,
                                    tilt);
    out.roll_rad = VRP_Math::clamp(out.roll_rad - pos.vy * 0.08 - VRP_Math::clamp(ay_j, -3.0, 3.0) * 0.02, -tilt, tilt);
  } else {
    out.thrust_base = hover_throttle_;
  }

  if (nav.valid) {
    out.thrust_base = static_cast<float>(
        VRP_Math::clamp(static_cast<double>(out.thrust_base) + nav.alt_error_m * 0.04, 0.35, 0.9));
  }

  return out;
}

std::string format_pos_control(const PosControlSetpoint &sp) {
  std::ostringstream oss;
  oss << "POSCTL roll=" << sp.roll_rad << " pitch=" << sp.pitch_rad << " yaw_rate=" << sp.yaw_rate_rad_s
      << " thr=" << sp.thrust_base;
  return oss.str();
}

} // namespace vrp
