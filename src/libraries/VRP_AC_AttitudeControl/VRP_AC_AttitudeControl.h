#pragma once
/**
 * @module  libraries/VRP_AC_AttitudeControl
 * @dal     B
 * @req     VRP-LLRD-AC_AttitudeControl
 * @parity  ArduPilot AC_AttitudeControl
 * @status  partial
 */
/**
 * @module  libraries/VRP_AC_AttitudeControl
 * @dal     B
 * @req     VRP-LLRD-AC_AttitudeControl
 */
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_PID/VRP_PID.h"

namespace vrp {

class VRP_AC_AttitudeControl {
public:
  bool init();
  ControlTorque update(const Attitude &attitude, const AttitudeSetpoint &sp, double dt_s);

private:
  PIDController roll_pid_{4.5, 0.0, 0.05, 0.3};
  PIDController pitch_pid_{4.5, 0.0, 0.05, 0.3};
};

} // namespace vrp
