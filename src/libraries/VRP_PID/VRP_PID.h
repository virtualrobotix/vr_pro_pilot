#pragma once
/**
 * @module  libraries/VRP_PID
 * @dal     B
 * @req     VRP-LLRD-PID
 * @parity  ArduPilot PID
 * @status  partial
 */
/**
 * @module  libraries/VRP_PID
 * @dal     B
 * @req     VRP-LLRD-PID
 */
namespace vrp {

class PIDController {
public:
  PIDController(double kp, double ki, double kd, double i_max);

  double update(double setpoint, double measurement, double dt_s);
  void reset();

private:
  double kp_;
  double ki_;
  double kd_;
  double i_max_;
  double integrator_{0.0};
  double prev_error_{0.0};
  bool have_prev_{false};
};

} // namespace vrp
