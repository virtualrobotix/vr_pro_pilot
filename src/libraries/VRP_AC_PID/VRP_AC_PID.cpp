#include "libraries/VRP_AC_PID/VRP_AC_PID.h"

#include "libraries/VRP_Math/VRP_Math.h"

#include <sstream>

namespace vrp {

bool VRP_AC_PID::init() {
  integral_ = 0.0F;
  return true;
}

AcPidState VRP_AC_PID::update(bool armed, float error) {
  AcPidState out{};
  out.active = armed;
  out.kp = 0.18F;
  out.ki = 0.025F;
  out.kd = 0.012F;
  if (!armed) {
    integral_ = 0.0F;
    last_error_ = 0.0F;
    return out;
  }
  integral_ = VRP_Math::clamp(integral_ + error * 0.02F, -0.5F, 0.5F);
  const float deriv = error - last_error_;
  last_error_ = error;
  out.output = VRP_Math::clamp(out.kp * error + out.ki * integral_ + out.kd * deriv, -1.0F, 1.0F);
  return out;
}

std::string format_ac_pid(const AcPidState &s) {
  std::ostringstream oss;
  oss << "ACPID active=" << (s.active ? 1 : 0) << " kp=" << s.kp << " ki=" << s.ki << " kd=" << s.kd
      << " out=" << s.output;
  return oss.str();
}

} // namespace vrp
