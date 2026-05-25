#include "libraries/VRP_BLHeli/VRP_BLHeli.h"

#include <sstream>

namespace vrp {

bool VRP_BLHeli::init() {
  seq_ = 0;
  return true;
}

BLHeliState VRP_BLHeli::update(float throttle, bool armed) {
  BLHeliState out{};
  out.esc_count = armed ? 4 : 0;
  out.rpm = static_cast<uint16_t>(throttle * 12000.0F);
  out.temp_c = 25.0F + throttle * 40.0F;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_blheli(const BLHeliState &s) {
  std::ostringstream oss;
  oss << "BLHELI esc=" << static_cast<int>(s.esc_count) << " rpm=" << s.rpm << " temp=" << s.temp_c;
  return oss.str();
}

} // namespace vrp
