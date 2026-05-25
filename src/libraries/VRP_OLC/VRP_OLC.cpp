#include "libraries/VRP_OLC/VRP_OLC.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_OLC::init() {
  points_ = 0;
  distance_m_ = 0.0;
  return true;
}

OlcState VRP_OLC::update(bool armed, double dx_m, double dy_m) {
  OlcState out{};
  out.logging = armed;
  if (armed) {
    const double seg = std::sqrt(dx_m * dx_m + dy_m * dy_m);
    if (seg > 0.05) {
      distance_m_ += seg;
      ++points_;
    }
  }
  out.points = points_;
  out.distance_m = distance_m_;
  return out;
}

std::string format_olc(const OlcState &s) {
  std::ostringstream oss;
  oss << "OLC log=" << (s.logging ? 1 : 0) << " points=" << s.points << " dist_m=" << static_cast<int>(s.distance_m);
  return oss.str();
}

} // namespace vrp
