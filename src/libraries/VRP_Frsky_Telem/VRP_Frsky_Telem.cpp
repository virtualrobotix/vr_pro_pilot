#include "libraries/VRP_Frsky_Telem/VRP_Frsky_Telem.h"

#include <sstream>

namespace vrp {

bool VRP_Frsky_Telem::init() {
  seq_ = 0;
  return true;
}

std::string VRP_Frsky_Telem::update(const std::string &mode, const Attitude &att, const BatteryStatus &batt,
                                      const LocalPosition &pos, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "FRSKY seq=" << seq_ << " mode=" << mode << " roll=" << att.roll_rad << " pitch=" << att.pitch_rad
      << " alt=" << -pos.z << " batt=" << batt.remaining_pct << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
