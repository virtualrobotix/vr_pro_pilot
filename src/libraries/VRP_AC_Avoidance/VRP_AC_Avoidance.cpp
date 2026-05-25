#include "libraries/VRP_AC_Avoidance/VRP_AC_Avoidance.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AC_Avoidance::init(double warn_m, double critical_m) {
  warn_m_ = warn_m;
  critical_m_ = critical_m;
  return true;
}

AvoidanceOutput VRP_AC_Avoidance::update(const AdsbVehicle &adsb, const ProximitySample &prox) {
  AvoidanceOutput out{};
  if (adsb.valid && adsb.distance_m <= warn_m_) {
    out.active = true;
    out.bearing_rad = std::atan2(-adsb.lat_e7 * 1e-7 + 45.0, -adsb.lon_e7 * 1e-7 + 9.0);
    out.speed_m_s = adsb.distance_m <= critical_m_ ? 2.5 : 1.2;
    out.source = "adsb";
    return out;
  }
  if (prox.valid && prox.breach) {
    out.active = true;
    out.bearing_rad = prox.angle_rad;
    out.speed_m_s = 1.0;
    out.source = "proximity";
    return out;
  }
  return out;
}

std::string format_avoidance(const AvoidanceOutput &o) {
  std::ostringstream oss;
  oss << "AVOIDANCE active=" << (o.active ? 1 : 0) << " src=" << o.source << " brg=" << o.bearing_rad
      << " spd=" << o.speed_m_s;
  return oss.str();
}

} // namespace vrp
