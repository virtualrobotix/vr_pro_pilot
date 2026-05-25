#include "libraries/VRP_ESC_Telem/VRP_ESC_Telem.h"

#include <sstream>

namespace vrp {

bool VRP_ESC_Telem::init() {
  seq_ = 0;
  return true;
}

EscTelemSample VRP_ESC_Telem::update(float throttle, float battery_v, uint64_t time_ms) {
  (void)time_ms;
  ++seq_;
  EscTelemSample out{};
  out.voltage_v = battery_v;
  out.current_a = throttle * 18.0F;
  out.rpm = throttle * 9200.0F;
  out.temperature_c = static_cast<uint8_t>(25.0F + throttle * 35.0F);
  out.valid = throttle > 0.05F;
  return out;
}

std::string format_esc_telem(const EscTelemSample &s) {
  std::ostringstream oss;
  oss << "ESC_TELEM volt=" << s.voltage_v << " amp=" << s.current_a << " rpm=" << s.rpm
      << " temp=" << static_cast<int>(s.temperature_c) << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
