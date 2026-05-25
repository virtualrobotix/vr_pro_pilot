#include "libraries/VRP_Radio/VRP_Radio.h"

#include "libraries/VRP_RSSI/VRP_RSSI.h"

#include <sstream>

namespace vrp {

bool VRP_Radio::init() {
  seq_ = 0;
  return true;
}

RadioState VRP_Radio::update(const RssiSample &rssi, bool armed) {
  RadioState out{};
  out.valid = rssi.valid;
  out.bound = armed && rssi.valid;
  out.rssi_pct = rssi.pct;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_radio(const RadioState &s) {
  std::ostringstream oss;
  oss << "RADIO bound=" << (s.bound ? 1 : 0) << " rssi=" << static_cast<int>(s.rssi_pct)
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
