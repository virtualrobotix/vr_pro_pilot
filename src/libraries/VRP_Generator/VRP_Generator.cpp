#include "libraries/VRP_Generator/VRP_Generator.h"

#include <sstream>

namespace vrp {

bool VRP_Generator::init() {
  idle_rpm_ = 3200.0;
  return true;
}

GeneratorState VRP_Generator::update(float throttle, bool armed) {
  GeneratorState out{};
  out.running = armed;
  out.rpm = armed ? idle_rpm_ + static_cast<double>(throttle) * 4000.0 : 0.0;
  out.load_pct = armed ? static_cast<double>(throttle) * 100.0 : 0.0;
  return out;
}

std::string format_generator(const GeneratorState &s) {
  std::ostringstream oss;
  oss << "GENERATOR run=" << (s.running ? 1 : 0) << " rpm=" << s.rpm << " load=" << s.load_pct;
  return oss.str();
}

} // namespace vrp
