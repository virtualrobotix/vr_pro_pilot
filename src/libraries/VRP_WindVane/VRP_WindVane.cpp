#include "libraries/VRP_WindVane/VRP_WindVane.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_WindVane::init() {
  base_speed_ = 3.5;
  return true;
}

WindSample VRP_WindVane::update(uint64_t tick) {
  WindSample out{};
  const double t = static_cast<double>(tick) * 0.02;
  out.speed_m_s = base_speed_ + std::sin(t * 0.2) * 0.8;
  out.direction_rad = std::fmod(t * 0.05, 6.28318530718);
  out.valid = true;
  return out;
}

std::string format_wind(const WindSample &s) {
  std::ostringstream oss;
  oss << "WIND spd=" << s.speed_m_s << " dir=" << s.direction_rad << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
