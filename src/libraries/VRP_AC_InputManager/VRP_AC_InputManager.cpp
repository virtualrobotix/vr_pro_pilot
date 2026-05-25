#include "libraries/VRP_AC_InputManager/VRP_AC_InputManager.h"

#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_Math/VRP_Math.h"

#include <sstream>

namespace vrp {

bool VRP_AC_InputManager::init() { return true; }

InputManagerState VRP_AC_InputManager::update(const RcChannels &rc, bool armed) {
  InputManagerState out{};
  out.valid = armed && rc.valid;
  out.mode_ch = out.valid ? 5 : 0;
  return out;
}

RcChannels VRP_AC_InputManager::apply_stabilize(const RcChannels &rc, double max_tilt_rad) {
  RcChannels out = rc;
  if (!rc.valid) {
    return out;
  }
  out.roll = static_cast<float>(VRP_Math::clamp(rc.roll, -1.0, 1.0));
  out.pitch = static_cast<float>(VRP_Math::clamp(rc.pitch, -1.0, 1.0));
  out.yaw = static_cast<float>(VRP_Math::clamp(rc.yaw, -1.0, 1.0));
  out.throttle = static_cast<float>(VRP_Math::clamp(rc.throttle, 0.0, 1.0));
  (void)max_tilt_rad;
  return out;
}

std::string format_input_manager(const InputManagerState &s) {
  std::ostringstream oss;
  oss << "INPUTM ch=" << static_cast<int>(s.mode_ch) << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
