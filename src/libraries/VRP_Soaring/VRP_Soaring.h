#pragma once
/**
 * @module  libraries/VRP_Soaring
 * @dal     C
 * @req     VRP-LLRD-AP_Soaring
 * @parity  ArduPilot AP_Soaring — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct SoaringState {
  bool thermal_active{false};
  double vario_m_s{0.0};
};

class VRP_Soaring {
public:
  bool init();
  SoaringState update(double alt_m, double climb_m_s);

private:
  double prev_alt_{0.0};
  bool have_prev_{false};
};

std::string format_soaring(const SoaringState &s);

} // namespace vrp
