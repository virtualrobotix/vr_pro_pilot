#pragma once
/** @module libraries/VRP_AC_Sprayer @dal     C @status  partial */
#include <string>

namespace vrp {

struct SprayerState {
  bool pump_on{false};
  float rate_l_min{0.0F};
};

class VRP_AC_Sprayer {
public:
  bool init();
  SprayerState update(bool armed, float aux2);
};

std::string format_sprayer(const SprayerState &s);

} // namespace vrp
