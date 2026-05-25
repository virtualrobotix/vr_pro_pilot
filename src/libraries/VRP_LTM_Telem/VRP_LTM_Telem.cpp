#include "libraries/VRP_LTM_Telem/VRP_LTM_Telem.h"

#include <sstream>

namespace vrp {

bool VRP_LTM_Telem::init() {
  seq_ = 0;
  return true;
}

std::string VRP_LTM_Telem::update(const LocalPosition &pos, const GpsSample &gps, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "LTM seq=" << seq_ << " x=" << pos.x << " y=" << pos.y << " lat=" << gps.lat_deg << " lon=" << gps.lon_deg
      << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
