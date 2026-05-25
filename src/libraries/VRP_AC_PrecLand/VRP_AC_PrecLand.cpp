#include "libraries/VRP_AC_PrecLand/VRP_AC_PrecLand.h"

#include "libraries/VRP_RangeFinder/VRP_RangeFinder.h"

#include <sstream>

namespace vrp {

bool VRP_AC_PrecLand::init() {
  seq_ = 0;
  return true;
}

PrecLandState VRP_AC_PrecLand::update(const RangeFinderSample &rng, bool armed, const std::string &mode) {
  PrecLandState out{};
  out.active = armed && (mode == "Land" || mode == "Loiter" || mode == "Auto" || mode == "RTL");
  out.alt_m = rng.valid ? rng.distance_m : 0.0;
  out.target_ok = out.active && rng.valid && rng.distance_m < 2.0;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_prec_land(const PrecLandState &s) {
  std::ostringstream oss;
  oss << "PRECLAND active=" << (s.active ? 1 : 0) << " target_ok=" << (s.target_ok ? 1 : 0)
      << " alt=" << s.alt_m;
  return oss.str();
}

} // namespace vrp
