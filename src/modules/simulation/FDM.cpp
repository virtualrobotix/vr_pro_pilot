#include "modules/simulation/FDM.h"

#include "libraries/VRP_Math/VRP_Math.h"

#include <cmath>

namespace vrp {

void FDM::step(const std::string &vehicle, double dt_s, FDMState &state, const FDMNavInput *nav) const {
  const double prev_yaw = state.yaw_deg;
  if (vehicle == "quad") {
    if (nav != nullptr && nav->valid) {
      const double speed = nav->target_speed_m_s * nav->speed_scale;
      state.x += std::cos(nav->bearing_rad) * speed * dt_s;
      state.y += std::sin(nav->bearing_rad) * speed * dt_s;
      const double climb_m_s = VRP_Math::clamp(nav->alt_error_m * 0.5, -3.0, 3.0);
      state.z += climb_m_s * dt_s;
      state.yaw_deg = VRP_Math::rad_to_deg(nav->bearing_rad);
    } else if (nav != nullptr && nav->guided_climb) {
      const double dz = nav->guided_target_z - state.z;
      const double rate = (nav->guided_target_z >= -0.5) ? 8.0 : 0.8;
      const double climb_m_s = VRP_Math::clamp(dz * rate, -10.0, 10.0);
      state.z += climb_m_s * dt_s;
      if (nav->guided_target_z >= -0.5) {
        state.z = VRP_Math::clamp(state.z, -150.0, 0.0);
      }
    } else {
      state.z -= 0.5 * dt_s;
    }
    state.yaw_deg += (nav != nullptr && nav->valid) ? 0.0 : 2.0 * dt_s;
    state.pitch_deg = VRP_Math::clamp(state.pitch_deg + 0.5 * dt_s, -15.0, 15.0);
  } else if (vehicle == "boat") {
    state.x += 1.2 * dt_s;
    state.yaw_deg += 1.0 * dt_s;
  } else if (vehicle == "vtol") {
    state.x += 2.0 * dt_s;
    state.z -= 0.2 * dt_s;
  } else if (vehicle == "subsea") {
    state.z -= 0.3 * dt_s;
    state.x += 0.4 * dt_s;
  }

  state.roll_deg = 0.0;
  state.ax = 0.0;
  state.ay = 0.0;
  state.az = -9.80665;
  state.gx = VRP_Math::deg_to_rad(state.roll_deg);
  state.gy = VRP_Math::deg_to_rad(state.pitch_deg);
  state.gz = VRP_Math::deg_to_rad(state.yaw_deg - prev_yaw) / dt_s;
  (void)model_;
}

} // namespace vrp
