#include "libraries/VRP_Quicktune/VRP_Quicktune.h"

#include <sstream>

namespace vrp {

bool VRP_Quicktune::init() {
  step_ = 0;
  return true;
}

QuicktuneState VRP_Quicktune::update(bool armed, float aux1, uint64_t tick) {
  QuicktuneState out{};
  out.active = armed && aux1 > 0.5F;
  if (out.active) {
    step_ = static_cast<uint8_t>((tick / 100) % 5);
  }
  out.step = step_;
  out.pct = out.active ? static_cast<uint8_t>(20 * (step_ + 1)) : 0;
  return out;
}

std::string format_quicktune(const QuicktuneState &s) {
  std::ostringstream oss;
  oss << "QUICKTUNE active=" << (s.active ? 1 : 0) << " step=" << static_cast<int>(s.step)
      << " pct=" << static_cast<int>(s.pct);
  return oss.str();
}

} // namespace vrp
