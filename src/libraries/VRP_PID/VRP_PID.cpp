#include "libraries/VRP_PID/VRP_PID.h"

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

PIDController::PIDController(double kp, double ki, double kd, double i_max)
    : kp_(kp), ki_(ki), kd_(kd), i_max_(i_max) {}

double PIDController::update(double setpoint, double measurement, double dt_s) {
  const double error = setpoint - measurement;
  integrator_ = VRP_Math::clamp(integrator_ + error * dt_s, -i_max_, i_max_);
  double derivative = 0.0;
  if (have_prev_ && dt_s > 0.0) {
    derivative = (error - prev_error_) / dt_s;
  }
  prev_error_ = error;
  have_prev_ = true;
  return kp_ * error + ki_ * integrator_ + kd_ * derivative;
}

void PIDController::reset() {
  integrator_ = 0.0;
  prev_error_ = 0.0;
  have_prev_ = false;
}

} // namespace vrp
