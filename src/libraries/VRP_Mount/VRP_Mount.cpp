#include "libraries/VRP_Mount/VRP_Mount.h"

#include <sstream>

namespace vrp {

bool VRP_Mount::init() {
  neutral_pitch_ = -45.0;
  return true;
}

MountState VRP_Mount::update(const Attitude &att, bool armed) {
  MountState out{};
  out.active = armed;
  out.yaw_deg = att.yaw_rad * 57.2957795;
  out.pitch_deg = neutral_pitch_ + att.pitch_rad * 57.2957795 * 0.25;
  return out;
}

std::string format_mount(const MountState &s) {
  std::ostringstream oss;
  oss << "MOUNT yaw=" << s.yaw_deg << " pitch=" << s.pitch_deg << " active=" << (s.active ? 1 : 0);
  return oss.str();
}

} // namespace vrp
