#include "libraries/VRP_AC_AutoTune/VRP_AC_AutoTune.h"

#include <sstream>

namespace vrp {

bool VRP_AC_AutoTune::init() {
  step_ = 0;
  return true;
}

AutoTuneState VRP_AC_AutoTune::update(bool armed, float aux1, uint64_t tick) {
  AutoTuneState out{};
  out.active = armed && aux1 > 0.75F;
  if (out.active) {
    step_ = static_cast<uint8_t>((tick % 4) + 1);
  }
  out.step = step_;
  out.pct = out.active ? static_cast<uint8_t>(25 * step_) : 0;
  return out;
}

std::string format_autotune(const AutoTuneState &s) {
  std::ostringstream oss;
  oss << "AUTOTUNE active=" << (s.active ? 1 : 0) << " step=" << static_cast<int>(s.step)
      << " pct=" << static_cast<int>(s.pct);
  return oss.str();
}

} // namespace vrp
