#include "libraries/VRP_Winch/VRP_Winch.h"

#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Winch::init() {
  line_m_ = 10.0;
  return true;
}

WinchState VRP_Winch::update(float command, bool armed) {
  WinchState out{};
  out.active = armed;
  if (armed) {
    line_m_ = VRP_Math::clamp(line_m_ - static_cast<double>(command) * 0.05, 0.0, 50.0);
    out.tension_n = 20.0 + static_cast<double>(command) * 80.0;
  }
  out.line_m = line_m_;
  return out;
}

std::string format_winch(const WinchState &s) {
  std::ostringstream oss;
  oss << "WINCH line=" << s.line_m << " tension=" << s.tension_n << " active=" << (s.active ? 1 : 0);
  return oss.str();
}

} // namespace vrp
