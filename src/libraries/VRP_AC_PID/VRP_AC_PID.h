#pragma once
/** @module libraries/VRP_AC_PID @dal     C @status  partial */
#include <string>

namespace vrp {

struct AcPidState {
  float kp{0.0F};
  float ki{0.0F};
  float kd{0.0F};
  bool active{false};
};

class VRP_AC_PID {
public:
  bool init();
  AcPidState update(bool armed, float error);
};

std::string format_ac_pid(const AcPidState &s);

} // namespace vrp
