#include "libraries/VRP_Module/VRP_Module.h"
#include <sstream>

namespace vrp {

bool VRP_Module::init() { return true; }

ModuleState VRP_Module::update(uint64_t tick, bool armed) {
  ModuleState out{};
  if (armed) {
    out.count = static_cast<uint32_t>((tick % 50U) + 149U);
  }
  return out;
}

std::string format_module(const ModuleState &s) {
  std::ostringstream oss;
  oss << "MODULE count=" << s.count;
  return oss.str();
}

} // namespace vrp
