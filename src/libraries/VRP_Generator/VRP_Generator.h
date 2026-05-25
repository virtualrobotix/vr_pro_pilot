#pragma once
/**
 * @module  libraries/VRP_Generator
 * @dal     C
 * @req     VRP-LLRD-AP_Generator
 * @parity  ArduPilot AP_Generator — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct GeneratorState {
  double rpm{0.0};
  double load_pct{0.0};
  bool running{false};
};

class VRP_Generator {
public:
  bool init();
  GeneratorState update(float throttle, bool armed);

private:
  double idle_rpm_{3200.0};
};

std::string format_generator(const GeneratorState &s);

} // namespace vrp
