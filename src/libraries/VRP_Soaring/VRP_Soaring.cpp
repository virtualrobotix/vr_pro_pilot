#include "libraries/VRP_Soaring/VRP_Soaring.h"

#include <sstream>

namespace vrp {

bool VRP_Soaring::init() {
  have_prev_ = false;
  return true;
}

SoaringState VRP_Soaring::update(double alt_m, double climb_m_s) {
  SoaringState out{};
  if (have_prev_) {
    out.vario_m_s = climb_m_s != 0.0 ? climb_m_s : (alt_m - prev_alt_) / 0.02;
  }
  prev_alt_ = alt_m;
  have_prev_ = true;
  out.thermal_active = out.vario_m_s > 0.35;
  return out;
}

std::string format_soaring(const SoaringState &s) {
  std::ostringstream oss;
  oss << "SOARING thermal=" << (s.thermal_active ? 1 : 0) << " vario=" << s.vario_m_s;
  return oss.str();
}

} // namespace vrp
