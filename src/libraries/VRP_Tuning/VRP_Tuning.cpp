#include "libraries/VRP_Tuning/VRP_Tuning.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <sstream>

namespace vrp {

bool VRP_Tuning::init() {
  seq_ = 0;
  return true;
}

TuningState VRP_Tuning::update(const RcChannels &rc, bool armed) {
  TuningState out{};
  out.active = armed && rc.valid;
  out.channel = out.active ? 6 : 0;
  out.value = out.active ? rc.aux2 : 0.0F;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_tuning(const TuningState &s) {
  std::ostringstream oss;
  oss << "TUNING active=" << (s.active ? 1 : 0) << " ch=" << static_cast<int>(s.channel) << " val=" << s.value;
  return oss.str();
}

} // namespace vrp
