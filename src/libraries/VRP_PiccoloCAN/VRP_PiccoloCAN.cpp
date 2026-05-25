#include "libraries/VRP_PiccoloCAN/VRP_PiccoloCAN.h"

#include <sstream>

namespace vrp {

bool VRP_PiccoloCAN::init() {
  frames_ = 0;
  return true;
}

PiccoloCanState VRP_PiccoloCAN::update(bool armed, uint64_t tick) {
  PiccoloCanState out{};
  out.bus_up = armed;
  out.nodes = armed ? 2 : 0;
  out.frames = static_cast<uint32_t>(tick);
  ++frames_;
  (void)frames_;
  return out;
}

std::string format_piccolo_can(const PiccoloCanState &s) {
  std::ostringstream oss;
  oss << "PICCOLO can=" << (s.bus_up ? 1 : 0) << " nodes=" << static_cast<int>(s.nodes)
      << " frames=" << s.frames;
  return oss.str();
}

} // namespace vrp
