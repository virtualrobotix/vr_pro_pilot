#include "libraries/VRP_CRSF/VRP_CRSF.h"

#include <sstream>

namespace vrp {

bool VRP_CRSF::init() {
  seq_ = 0;
  return true;
}

std::string VRP_CRSF::update(const Attitude &att, const BatteryStatus &batt, const RssiSample &rssi, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "CRSF seq=" << seq_ << " roll=" << att.roll_rad << " pitch=" << att.pitch_rad
      << " batt=" << batt.remaining_pct << " rssi=" << static_cast<int>(rssi.pct) << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
