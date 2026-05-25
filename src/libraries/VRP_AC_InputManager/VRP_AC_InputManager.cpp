#include "libraries/VRP_AC_InputManager/VRP_AC_InputManager.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include <sstream>

namespace vrp {

bool VRP_AC_InputManager::init() { return true; }

InputManagerState VRP_AC_InputManager::update(const RcChannels &rc, bool armed) {
  InputManagerState out{};
  out.valid = armed && rc.valid;
  out.mode_ch = out.valid ? 5 : 0;
  return out;
}

std::string format_input_manager(const InputManagerState &s) {
  std::ostringstream oss;
  oss << "INPUTM ch=" << static_cast<int>(s.mode_ch) << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
