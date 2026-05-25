#include "libraries/VRP_OpenDroneID/VRP_OpenDroneID.h"

#include <sstream>

namespace vrp {

bool VRP_OpenDroneID::init() {
  seq_ = 0;
  return true;
}

std::string VRP_OpenDroneID::broadcast(const GpsSample &gps, bool armed, const std::string &mode, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "OPEN_DRONE_ID seq=" << seq_ << " lat=" << gps.lat_deg << " lon=" << gps.lon_deg << " alt=" << gps.alt_m
      << " armed=" << (armed ? 1 : 0) << " mode=" << mode << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
