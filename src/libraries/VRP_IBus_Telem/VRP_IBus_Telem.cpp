#include "libraries/VRP_IBus_Telem/VRP_IBus_Telem.h"

#include <sstream>

namespace vrp {

bool VRP_IBus_Telem::init() {
  seq_ = 0;
  return true;
}

std::string VRP_IBus_Telem::update(const Attitude &att, const BatteryStatus &batt, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "IBUS seq=" << seq_ << " roll=" << att.roll_rad << " pitch=" << att.pitch_rad
      << " batt=" << batt.remaining_pct << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
