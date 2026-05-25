#include "libraries/VRP_AC_PID/VRP_AC_PID.h"
#include <sstream>

namespace vrp {

bool VRP_AC_PID::init() { return true; }

AcPidState VRP_AC_PID::update(bool armed, float error) {
  AcPidState out{};
  out.active = armed;
  out.kp = 0.15F;
  out.ki = 0.02F;
  out.kd = 0.01F;
  (void)error;
  return out;
}

std::string format_ac_pid(const AcPidState &s) {
  std::ostringstream oss;
  oss << "ACPID active=" << (s.active ? 1 : 0) << " kp=" << s.kp << " ki=" << s.ki << " kd=" << s.kd;
  return oss.str();
}

} // namespace vrp
