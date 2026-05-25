#include "libraries/VRP_OSD/VRP_OSD.h"

#include <sstream>

namespace vrp {

bool VRP_OSD::init() { return true; }

std::string VRP_OSD::render(const std::string &vehicle_mode, const LocalPosition &pos, const BatteryStatus &battery,
                             bool armed) const {
  std::ostringstream oss;
  oss << "OSD mode=" << vehicle_mode << " alt=" << -pos.z << " spd=" << pos.vx << " batt=" << battery.remaining_pct
      << " arm=" << (armed ? 1 : 0);
  return oss.str();
}

} // namespace vrp
