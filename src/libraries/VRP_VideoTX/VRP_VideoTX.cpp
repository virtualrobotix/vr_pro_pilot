#include "libraries/VRP_VideoTX/VRP_VideoTX.h"

#include <sstream>

namespace vrp {

bool VRP_VideoTX::init() {
  base_mhz_ = 5740;
  return true;
}

VideoTxState VRP_VideoTX::update(bool armed, uint64_t tick) {
  VideoTxState out{};
  out.active = armed;
  out.channel_mhz = static_cast<uint16_t>(base_mhz_ + static_cast<uint16_t>((tick % 8U) * 5U));
  out.power_mw = armed ? 200U : 25U;
  return out;
}

std::string format_vtx(const VideoTxState &s) {
  std::ostringstream oss;
  oss << "VTX active=" << (s.active ? 1 : 0) << " mhz=" << s.channel_mhz << " mw=" << static_cast<int>(s.power_mw);
  return oss.str();
}

} // namespace vrp
