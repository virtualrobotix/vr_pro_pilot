#include "libraries/VRP_Volz_Protocol/VRP_Volz_Protocol.h"

#include <sstream>

namespace vrp {

bool VRP_Volz_Protocol::init() {
  seq_ = 0;
  return true;
}

VolzState VRP_Volz_Protocol::update(float command, bool armed, uint64_t tick) {
  VolzState out{};
  out.valid = armed;
  out.servo_id = armed ? 1 : 0;
  out.position_deg = command * 45.0F;
  ++seq_;
  (void)tick;
  (void)seq_;
  return out;
}

std::string format_volz(const VolzState &s) {
  std::ostringstream oss;
  oss << "VOLZ id=" << static_cast<int>(s.servo_id) << " pos=" << s.position_deg
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
