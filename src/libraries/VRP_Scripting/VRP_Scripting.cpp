#include "libraries/VRP_Scripting/VRP_Scripting.h"

namespace vrp {

bool VRP_Scripting::init(bool enable) {
  enabled_ = enable;
  return true;
}

std::string VRP_Scripting::update(uint64_t tick, const std::string &current_mode) {
  if (!enabled_) {
    return "SCRIPT idle";
  }
  if (tick == 4) {
    return "SCRIPT event=mode_hint:Auto";
  }
  (void)current_mode;
  return "SCRIPT ok";
}

} // namespace vrp
