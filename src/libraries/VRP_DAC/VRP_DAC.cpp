#include "libraries/VRP_DAC/VRP_DAC.h"
#include <sstream>

namespace vrp {

bool VRP_DAC::init() { return true; }

DacState VRP_DAC::update(float throttle, bool armed) {
  DacState out{};
  if (armed) {
    out.ch = 1;
    out.val = throttle;
  }
  return out;
}

std::string format_dac(const DacState &s) {
  std::ostringstream oss;
  oss << "DAC ch=" << static_cast<int>(s.ch) << " val=" << s.val;
  return oss.str();
}

} // namespace vrp
