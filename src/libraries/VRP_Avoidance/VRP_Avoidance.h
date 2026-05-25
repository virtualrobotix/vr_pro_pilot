#pragma once
/** @module libraries/VRP_Avoidance @dal     B @status  partial */
#include <string>

namespace vrp {

struct ApAvoidanceState {
  bool active{false};
  float margin_m{0.0F};
};

class VRP_Avoidance {
public:
  bool init();
  ApAvoidanceState update(bool armed, float prox_min_m);
};

std::string format_ap_avoidance(const ApAvoidanceState &s);

} // namespace vrp
