#include "libraries/VRP_TECS/VRP_TECS.h"

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_TECS::init(double target_alt_m, double target_speed_m_s) {
  target_alt_m_ = target_alt_m;
  target_speed_m_s_ = target_speed_m_s;
  return true;
}

TecsOutput VRP_TECS::update(double alt_m, double speed_m_s, double dt_s) {
  TecsOutput out{};
  const double alt_err = target_alt_m_ - alt_m;
  const double spd_err = target_speed_m_s_ - speed_m_s;
  out.pitch_rad = VRP_Math::clamp(-0.02 * alt_err - 0.01 * spd_err, -0.35, 0.15);
  out.throttle = VRP_Math::clamp(0.55 + 0.02 * spd_err + 0.01 * alt_err, 0.35, 0.9);
  (void)dt_s;
  return out;
}

} // namespace vrp
