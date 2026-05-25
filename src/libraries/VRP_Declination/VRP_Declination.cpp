#include "libraries/VRP_Declination/VRP_Declination.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_Declination::init() { return true; }

DeclinationState VRP_Declination::update(const GpsSample &gps) {
  DeclinationState out{};
  if (gps.valid) {
    const double lat_rad = gps.lat_deg * M_PI / 180.0;
    out.deg = static_cast<float>(11.5 * std::sin(lat_rad * 2.0));
  }
  return out;
}

std::string format_declination(const DeclinationState &s) {
  std::ostringstream oss;
  oss << "DECL deg=" << s.deg;
  return oss.str();
}

} // namespace vrp
