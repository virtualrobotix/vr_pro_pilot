#include "libraries/VRP_LightWareSerial/VRP_LightWareSerial.h"

#include "libraries/VRP_RangeFinder/VRP_RangeFinder.h"

#include <sstream>

namespace vrp {

bool VRP_LightWareSerial::init() {
  seq_ = 0;
  return true;
}

LightWareState VRP_LightWareSerial::update(const RangeFinderSample &rng, bool armed) {
  LightWareState out{};
  out.valid = armed && rng.valid;
  out.distance_m = rng.distance_m;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_lightware(const LightWareState &s) {
  std::ostringstream oss;
  oss << "LIGHTWARE dist=" << s.distance_m << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
