#include "libraries/VRP_NavEKF3/VRP_NavEKF3.h"

namespace vrp {

bool VRP_NavEKF3::init() {
  state_ = LocalPosition{};
  initialized_ = false;
  pos_var_ = 4.0;
  return true;
}

LocalPosition VRP_NavEKF3::update(const LocalPosition &measurement, double dt_s) {
  if (!initialized_) {
    state_ = measurement;
    state_.valid = measurement.valid;
    initialized_ = true;
    return state_;
  }

  const double process_var = 0.05 * dt_s;
  pos_var_ += process_var;

  const double k = pos_var_ / (pos_var_ + meas_var_);
  const double dx = measurement.x - state_.x;
  const double dy = measurement.y - state_.y;
  const double dz = measurement.z - state_.z;

  state_.x += k * dx;
  state_.y += k * dy;
  state_.z += k * dz;
  state_.vx = (dt_s > 0.0) ? dx / dt_s : 0.0;
  state_.vy = (dt_s > 0.0) ? dy / dt_s : 0.0;
  state_.vz = (dt_s > 0.0) ? dz / dt_s : 0.0;
  state_.valid = measurement.valid;
  pos_var_ *= (1.0 - k);
  return state_;
}

} // namespace vrp
