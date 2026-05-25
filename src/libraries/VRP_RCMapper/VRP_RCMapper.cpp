#include "libraries/VRP_RCMapper/VRP_RCMapper.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <sstream>

namespace vrp {

bool VRP_RCMapper::init() {
  seq_ = 0;
  return true;
}

RcMapState VRP_RCMapper::map(const RcChannels &rc) {
  RcMapState out{};
  out.valid = rc.valid;
  out.roll = rc.roll;
  out.pitch = rc.pitch;
  out.throttle = rc.throttle;
  out.yaw = rc.yaw;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_rc_map(const RcMapState &s) {
  std::ostringstream oss;
  oss << "RCMAP roll=" << s.roll << " pitch=" << s.pitch << " thr=" << s.throttle << " yaw=" << s.yaw
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
