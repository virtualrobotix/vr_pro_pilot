#include "libraries/VRP_SerialManager/VRP_SerialManager.h"

#include <sstream>

namespace vrp {

bool VRP_SerialManager::init() {
  ports_ = {1, 1, 1, 0, 0, 0};
  return true;
}

std::array<uint8_t, 6> VRP_SerialManager::port_active_mask(uint64_t tick) const {
  auto out = ports_;
  out[3] = static_cast<uint8_t>((tick % 4U) > 0U ? 1U : 0U);
  return out;
}

std::string format_serial_ports(const std::array<uint8_t, 6> &ports) {
  std::ostringstream oss;
  oss << "SERIAL p1=" << static_cast<int>(ports[0]) << " p2=" << static_cast<int>(ports[1])
      << " p3=" << static_cast<int>(ports[2]) << " p4=" << static_cast<int>(ports[3])
      << " p5=" << static_cast<int>(ports[4]) << " p6=" << static_cast<int>(ports[5]);
  return oss.str();
}

} // namespace vrp
