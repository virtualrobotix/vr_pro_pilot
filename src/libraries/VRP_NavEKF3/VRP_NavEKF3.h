#pragma once
/**
 * @module  libraries/VRP_NavEKF3
 * @dal     B
 * @req     VRP-LLRD-AP_NavEKF3
 * @parity  ArduPilot AP_NavEKF3
 * @status  partial
 */
/**
 * @module  libraries/VRP_NavEKF3
 * @dal     B
 * @req     VRP-LLRD-AP_NavEKF3
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_NavEKF3 {
public:
  bool init();
  LocalPosition update(const LocalPosition &measurement, double dt_s);

  const LocalPosition &state() const { return state_; }

private:
  LocalPosition state_{};
  double pos_var_{4.0};
  double meas_var_{0.25};
  bool initialized_{false};
};

} // namespace vrp
