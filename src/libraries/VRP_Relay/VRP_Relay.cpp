#include "libraries/VRP_Relay/VRP_Relay.h"

#include <sstream>

namespace vrp {

bool VRP_Relay::init() {
  last_.fill(0);
  return true;
}

std::array<uint8_t, 4> VRP_Relay::update(bool armed, uint64_t tick) {
  last_[0] = armed ? 1U : 0U;
  last_[1] = static_cast<uint8_t>((tick / 2U) % 2U);
  last_[2] = static_cast<uint8_t>((tick / 3U) % 2U);
  last_[3] = 0U;
  return last_;
}

std::string format_relay(const std::array<uint8_t, 4> &channels) {
  std::ostringstream oss;
  oss << "RELAY ch1=" << static_cast<int>(channels[0]) << " ch2=" << static_cast<int>(channels[1])
      << " ch3=" << static_cast<int>(channels[2]) << " ch4=" << static_cast<int>(channels[3]);
  return oss.str();
}

} // namespace vrp
