#include "libraries/VRP_SBusOut/VRP_SBusOut.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <sstream>

namespace vrp {

bool VRP_SBusOut::init() {
  seq_ = 0;
  return true;
}

SBusOutState VRP_SBusOut::update(const RcChannels &rc, bool armed, uint64_t tick) {
  SBusOutState out{};
  out.active = armed && rc.valid;
  out.channels = out.active ? 16 : 0;
  out.frames = static_cast<uint32_t>(tick);
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_sbus_out(const SBusOutState &s) {
  std::ostringstream oss;
  oss << "SBUS active=" << (s.active ? 1 : 0) << " ch=" << static_cast<int>(s.channels) << " frames=" << s.frames;
  return oss.str();
}

} // namespace vrp
