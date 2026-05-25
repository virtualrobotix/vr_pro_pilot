#include "libraries/VRP_ICEngine/VRP_ICEngine.h"

#include <sstream>

namespace vrp {

bool VRP_ICEngine::init() {
  seq_ = 0;
  return true;
}

ICEngineState VRP_ICEngine::update(float throttle, bool armed) {
  ICEngineState out{};
  out.running = armed && throttle > 0.1F;
  out.throttle_pct = throttle * 100.0F;
  out.rpm = static_cast<uint16_t>(800.0F + throttle * 4200.0F);
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_icengine(const ICEngineState &s) {
  std::ostringstream oss;
  oss << "ICENGINE run=" << (s.running ? 1 : 0) << " rpm=" << s.rpm << " thr=" << s.throttle_pct;
  return oss.str();
}

} // namespace vrp
