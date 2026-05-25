#pragma once
/**
 * @module  libraries/VRP_OLC
 * @dal     C
 * @req     VRP-LLRD-AP_OLC
 * @parity  ArduPilot AP_OLC — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct OlcState {
  uint32_t points{0};
  double distance_m{0.0};
  bool logging{false};
};

class VRP_OLC {
public:
  bool init();
  OlcState update(bool armed, double dx_m, double dy_m);

private:
  uint32_t points_{0};
  double distance_m_{0.0};
};

std::string format_olc(const OlcState &s);

} // namespace vrp
