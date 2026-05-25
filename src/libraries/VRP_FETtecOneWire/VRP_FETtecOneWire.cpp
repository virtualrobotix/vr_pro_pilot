#include "libraries/VRP_FETtecOneWire/VRP_FETtecOneWire.h"

#include <sstream>

namespace vrp {

bool VRP_FETtecOneWire::init() {
  seq_ = 0;
  return true;
}

FETtecState VRP_FETtecOneWire::update(float throttle, bool armed) {
  FETtecState out{};
  out.esc_count = armed ? 4 : 0;
  out.rpm = static_cast<uint16_t>(throttle * 11000.0F);
  out.temp_c = 30.0F + throttle * 35.0F;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_fettec(const FETtecState &s) {
  std::ostringstream oss;
  oss << "FETTEC esc=" << static_cast<int>(s.esc_count) << " rpm=" << s.rpm << " temp=" << s.temp_c;
  return oss.str();
}

} // namespace vrp
