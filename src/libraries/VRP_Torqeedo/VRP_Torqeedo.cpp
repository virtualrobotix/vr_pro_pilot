#include "libraries/VRP_Torqeedo/VRP_Torqeedo.h"

#include <sstream>

namespace vrp {

bool VRP_Torqeedo::init() {
  seq_ = 0;
  return true;
}

TorqeedoState VRP_Torqeedo::update(float throttle, bool armed, float voltage_v) {
  TorqeedoState out{};
  out.motor_on = armed && throttle > 0.05F;
  out.rpm = static_cast<uint16_t>(throttle * 1800.0F);
  out.power_w = out.motor_on ? throttle * voltage_v * 8.0F : 0.0F;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_torqeedo(const TorqeedoState &s) {
  std::ostringstream oss;
  oss << "TORQEEDO on=" << (s.motor_on ? 1 : 0) << " rpm=" << s.rpm << " power_w=" << static_cast<int>(s.power_w);
  return oss.str();
}

} // namespace vrp
