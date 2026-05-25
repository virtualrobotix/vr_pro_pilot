#include "modules/simulation/FDM.h"

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

void FDM::step(const std::string &vehicle, double dt_s, FDMState &state) const {
  const double prev_yaw = state.yaw_deg;
  if (vehicle == "quad") {
    state.z -= 0.5 * dt_s;
    state.yaw_deg += 2.0 * dt_s;
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
