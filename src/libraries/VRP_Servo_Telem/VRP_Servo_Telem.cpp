#include "libraries/VRP_Servo_Telem/VRP_Servo_Telem.h"

#include <sstream>

namespace vrp {

bool VRP_Servo_Telem::init() {
  seq_ = 0;
  return true;
}

ServoTelemSample VRP_Servo_Telem::update(float servo_cmd, float bus_v, uint64_t time_ms) {
  (void)time_ms;
  ++seq_;
  ServoTelemSample out{};
  out.position_pct = servo_cmd * 100.0F;
  out.voltage_v = bus_v;
  out.temperature_c = static_cast<uint8_t>(30.0F + servo_cmd * 15.0F);
  out.valid = true;
  return out;
}

std::string format_servo_telem(const ServoTelemSample &s) {
  std::ostringstream oss;
  oss << "SERVO_TELEM pos=" << s.position_pct << " volt=" << s.voltage_v << " temp=" << static_cast<int>(s.temperature_c)
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
