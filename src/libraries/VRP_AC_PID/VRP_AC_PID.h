#pragma once
/** @module libraries/VRP_AC_PID @dal     C @status  partial */
#include <string>

namespace vrp {

struct AcPidState {
  bool active{false};
  float kp{0.0F};
  float ki{0.0F};
  float kd{0.0F};
  float output{0.0F};
};

class VRP_AC_PID {
public:
  bool init();
  AcPidState update(bool armed, float error);

private:
  float integral_{0.0F};
  float last_error_{0.0F};
};

std::string format_ac_pid(const AcPidState &s);

} // namespace vrp
