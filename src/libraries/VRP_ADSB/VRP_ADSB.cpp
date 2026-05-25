#include "libraries/VRP_ADSB/VRP_ADSB.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_ADSB::init(double intruder_x_m) {
  base_x_ = intruder_x_m;
  base_y_ = 0.0;
  return true;
}

void VRP_ADSB::set_intruder_x(double x_m) { base_x_ = x_m; }

AdsbThreat VRP_ADSB::classify(double distance_m) const {
  if (distance_m <= 30.0) {
    return AdsbThreat::Critical;
  }
  if (distance_m <= 80.0) {
    return AdsbThreat::Warn;
  }
  return AdsbThreat::Safe;
}

AdsbVehicle VRP_ADSB::update(uint64_t tick, double own_x_m, double own_y_m, double own_alt_m) {
  AdsbVehicle v{};
  const double t = static_cast<double>(tick) * 0.02;
  const double tx = base_x_ + std::sin(t * 0.15) * 15.0;
  const double ty = base_y_ + std::cos(t * 0.11) * 8.0;
  const double dx = tx - own_x_m;
  const double dy = ty - own_y_m;
  v.distance_m = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  v.lat_e7 = static_cast<int32_t>((45.0 + ty / 111320.0) * 1e7);
  v.lon_e7 = static_cast<int32_t>((9.0 + tx / 111320.0) * 1e7);
  v.alt_mm = 150000;
  v.vertical_sep_m = std::abs(150.0 - own_alt_m);
  v.heading_cdeg = static_cast<uint16_t>(std::fmod(t * 400.0, 36000.0));
  v.squawk = 1200;
  v.icao = 0xABCDEF;
  v.threat = classify(v.distance_m);
  v.valid = true;
  return v;
}

const char *adsb_threat_name(AdsbThreat t) {
  switch (t) {
  case AdsbThreat::Critical:
    return "critical";
  case AdsbThreat::Warn:
    return "warn";
  case AdsbThreat::Safe:
  default:
    return "safe";
  }
}

std::string format_adsb(const AdsbVehicle &v) {
  std::ostringstream oss;
  oss << "ADSB icao=0x" << std::hex << v.icao << std::dec << " dist=" << v.distance_m << " vsep=" << v.vertical_sep_m
      << " threat=" << adsb_threat_name(v.threat) << " hdg=" << v.heading_cdeg << " valid=" << (v.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
