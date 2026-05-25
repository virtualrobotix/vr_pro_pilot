#include "libraries/VRP_Avoidance/VRP_Avoidance.h"
#include <sstream>

namespace vrp {

bool VRP_Avoidance::init() { return true; }

ApAvoidanceState VRP_Avoidance::update(bool armed, float prox_min_m) {
  ApAvoidanceState out{};
  out.active = armed && prox_min_m < 5.0F;
  out.margin_m = prox_min_m;
  return out;
}

std::string format_ap_avoidance(const ApAvoidanceState &s) {
  std::ostringstream oss;
  oss << "APAVOID active=" << (s.active ? 1 : 0) << " margin=" << s.margin_m;
  return oss.str();
}

} // namespace vrp
