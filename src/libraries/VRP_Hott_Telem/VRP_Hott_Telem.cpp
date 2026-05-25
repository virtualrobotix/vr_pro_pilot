#include "libraries/VRP_Hott_Telem/VRP_Hott_Telem.h"

#include <sstream>

namespace vrp {

bool VRP_Hott_Telem::init() {
  seq_ = 0;
  return true;
}

std::string VRP_Hott_Telem::update(const Attitude &att, const LocalPosition &pos, const BatteryStatus &batt,
                                   uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "HOTT seq=" << seq_ << " roll=" << att.roll_rad << " pitch=" << att.pitch_rad << " alt=" << -pos.z
      << " batt=" << batt.remaining_pct << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
