#include "libraries/VRP_MSP/VRP_MSP.h"

#include <sstream>

namespace vrp {

bool VRP_MSP::init() {
  seq_ = 0;
  return true;
}

std::string VRP_MSP::update(const Attitude &att, const LocalPosition &pos, const BatteryStatus &batt, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "MSP seq=" << seq_ << " roll=" << att.roll_rad << " pitch=" << att.pitch_rad << " alt=" << -pos.z
      << " batt=" << batt.remaining_pct << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
