#include "libraries/VRP_Airspeed/VRP_Airspeed.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_Airspeed::init() {
  offset_m_s_ = 0.0;
  return true;
}

AirspeedSample VRP_Airspeed::update(double ground_speed_m_s, uint64_t time_us) {
  (void)time_us;
  AirspeedSample out{};
  out.speed_m_s = std::max(0.0, ground_speed_m_s - offset_m_s_);
  out.differential_pa = 0.5 * 1.225 * out.speed_m_s * out.speed_m_s;
  out.valid = true;
  return out;
}

std::string format_airspeed(const AirspeedSample &s) {
  std::ostringstream oss;
  oss << "AIRSPEED spd=" << s.speed_m_s << " pa=" << s.differential_pa << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
