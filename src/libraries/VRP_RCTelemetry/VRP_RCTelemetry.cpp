#include "libraries/VRP_RCTelemetry/VRP_RCTelemetry.h"

#include <sstream>

namespace vrp {

bool VRP_RCTelemetry::init() {
  seq_ = 0;
  return true;
}

std::string VRP_RCTelemetry::update(const RcChannels &rc, const RssiSample &rssi, uint64_t time_ms) {
  ++seq_;
  std::ostringstream oss;
  oss << "RC_TELEM seq=" << seq_ << " roll=" << rc.roll << " throttle=" << rc.throttle
      << " rssi=" << static_cast<int>(rssi.pct) << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
