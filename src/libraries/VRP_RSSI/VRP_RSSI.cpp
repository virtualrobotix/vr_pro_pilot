#include "libraries/VRP_RSSI/VRP_RSSI.h"

#include <algorithm>
#include <sstream>

namespace vrp {

bool VRP_RSSI::init() {
  base_pct_ = 92;
  return true;
}

RssiSample VRP_RSSI::update(uint64_t tick, bool gcs_link) {
  RssiSample out{};
  const int drift = static_cast<int>((tick % 7) - 3);
  out.pct = static_cast<uint8_t>(std::clamp(static_cast<int>(base_pct_) + drift + (gcs_link ? 3 : -8), 0, 100));
  out.valid = true;
  return out;
}

std::string format_rssi(const RssiSample &s) {
  std::ostringstream oss;
  oss << "RSSI pct=" << static_cast<int>(s.pct) << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
