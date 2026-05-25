#include "libraries/VRP_Devo_Telem/VRP_Devo_Telem.h"

#include <sstream>

namespace vrp {

bool VRP_Devo_Telem::init() {
  seq_ = 0;
  return true;
}

std::string VRP_Devo_Telem::update(const LocalPosition &pos, const BatteryStatus &batt, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "DEVO seq=" << seq_ << " alt=" << -pos.z << " batt=" << batt.remaining_pct << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
