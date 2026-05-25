#include "libraries/VRP_Sailboat/VRP_Sailboat.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

namespace {
double wrap_pi(double rad) {
  while (rad > 3.141592653589793) {
    rad -= 6.283185307179586;
  }
  while (rad < -3.141592653589793) {
    rad += 6.283185307179586;
  }
  return rad;
}
} // namespace

bool VRP_Sailboat::init(double max_speed_m_s) {
  max_speed_m_s_ = max_speed_m_s;
  return true;
}

SailboatOutput VRP_Sailboat::update(const Attitude &attitude, const WindSample &wind, float desired_turn_rate_rad_s,
                                    float desired_speed_m_s, bool manual, float rc_sail, float rc_rudder, bool armed) {
  SailboatOutput out{};
  out.active = armed;
  if (!armed) {
    return out;
  }

  if (manual) {
    out.sail_sheet = VRP_Math::clamp(rc_sail, 0.0F, 1.0F);
    out.rudder = VRP_Math::clamp(rc_rudder, -1.0F, 1.0F);
    out.steering = out.rudder;
    out.throttle = out.sail_sheet * 0.8F;
    return out;
  }

  const double wind_from = wind.valid ? wind.direction_rad : 0.0;
  const double rel_wind = wrap_pi(wind_from - attitude.yaw_rad);
  const double abs_rel = std::abs(rel_wind);
  out.sail_sheet = static_cast<float>(VRP_Math::clamp(0.35 + abs_rel / 3.141592653589793, 0.15, 1.0));
  const double drive = wind.valid ? wind.speed_m_s * std::cos(rel_wind) * static_cast<double>(out.sail_sheet) : 0.0;
  const double speed_ratio = max_speed_m_s_ > 0.1 ? drive / max_speed_m_s_ : 0.0;
  out.throttle = static_cast<float>(VRP_Math::clamp(speed_ratio, -0.2, 1.0));
  out.steering = static_cast<float>(VRP_Math::clamp(desired_turn_rate_rad_s / 0.8, -1.0, 1.0));
  if (desired_speed_m_s > 0.1F) {
    out.steering = static_cast<float>(
        VRP_Math::clamp(out.steering + static_cast<float>(desired_speed_m_s / max_speed_m_s_ * 0.15), -1.0, 1.0));
  }
  out.rudder = out.steering;
  return out;
}

std::string format_sailboat(const SailboatOutput &s) {
  std::ostringstream oss;
  oss << "SAIL active=" << (s.active ? 1 : 0) << " sheet=" << s.sail_sheet << " rudder=" << s.rudder
      << " thr=" << s.throttle << " steer=" << s.steering;
  return oss.str();
}

} // namespace vrp
