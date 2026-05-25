#pragma once
/**
 * @module  libraries/VRP_Winch
 * @dal     C
 * @req     VRP-LLRD-AP_Winch
 * @parity  ArduPilot AP_Winch — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct WinchState {
  double line_m{0.0};
  double tension_n{0.0};
  bool active{false};
};

class VRP_Winch {
public:
  bool init();
  WinchState update(float command, bool armed);

private:
  double line_m_{10.0};
};

std::string format_winch(const WinchState &s);

} // namespace vrp
