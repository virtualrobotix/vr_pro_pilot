#include "libraries/VRP_KDECAN/VRP_KDECAN.h"

#include <sstream>

namespace vrp {

bool VRP_KDECAN::init() {
  seq_ = 0;
  return true;
}

KdeCanState VRP_KDECAN::update(float throttle, bool armed, uint64_t tick) {
  KdeCanState out{};
  out.bus_up = armed;
  out.nodes = armed ? 4 : 0;
  out.rpm = static_cast<uint16_t>(throttle * 10000.0F);
  ++seq_;
  (void)tick;
  (void)seq_;
  return out;
}

std::string format_kde_can(const KdeCanState &s) {
  std::ostringstream oss;
  oss << "KDECAN bus=" << (s.bus_up ? 1 : 0) << " nodes=" << static_cast<int>(s.nodes) << " rpm=" << s.rpm;
  return oss.str();
}

} // namespace vrp
