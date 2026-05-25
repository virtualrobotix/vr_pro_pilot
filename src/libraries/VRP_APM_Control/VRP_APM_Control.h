#pragma once
/**
 * @module  libraries/VRP_APM_Control
 * @dal     B
 * @req     VRP-LLRD-APM_Control
 * @parity  ArduPilot APM_Control — clean-room BSD rewrite
 * @status  partial
 */
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_PID/VRP_PID.h"

namespace vrp {

struct FwNavSetpoint {
  double bearing_rad{0.0};
  double speed_m_s{10.0};
  bool valid{false};
};

struct FwControlSetpoint {
  double roll_rad{0.0};
  double pitch_rad{0.0};
  double yaw_rate_rad_s{0.0};
};

class VRP_APM_Control {
public:
  bool init();
  FwControlSetpoint update(const Attitude &attitude, const FwNavSetpoint &nav, const FwControlSetpoint &tecs_sp,
                           double dt_s);

private:
  PIDController roll_pid_{1.2, 0.01, 0.08, 0.35};
  PIDController pitch_pid_{1.0, 0.01, 0.06, 0.25};
};

} // namespace vrp
