#include "libraries/VRP_Baro/VRP_Baro.h"

#include <cmath>

namespace vrp {

bool VRP_Baro::init() { return true; }

BaroSample VRP_Baro::update(double alt_m, uint64_t time_us) {
  BaroSample out{};
  out.alt_m = alt_m;
  out.pressure_pa = kSeaLevelPa * std::pow(1.0 - alt_m / 44330.0, 5.255);
  out.valid = true;
  out.time_us = time_us;
  return out;
}

} // namespace vrp
