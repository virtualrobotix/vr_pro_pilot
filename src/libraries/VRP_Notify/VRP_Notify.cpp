#include "libraries/VRP_Notify/VRP_Notify.h"

#include <sstream>

namespace vrp {

bool VRP_Notify::init() {
  seq_ = 0;
  return true;
}

std::string VRP_Notify::update(bool armed, const std::string &mode, uint64_t tick) {
  ++seq_;
  std::ostringstream oss;
  const char *pattern = armed ? (mode == "RTL" ? "flash_red" : "breathe_green") : "solid_blue";
  oss << "NOTIFY seq=" << seq_ << " armed=" << (armed ? 1 : 0) << " mode=" << mode << " pattern=" << pattern;
  return oss.str();
}

} // namespace vrp
