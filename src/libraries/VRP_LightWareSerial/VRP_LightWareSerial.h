#pragma once
/**
 * @module  libraries/VRP_LightWareSerial
 * @dal     C
 * @req     VRP-LLRD-AP_LightWareSerial
 * @parity  ArduPilot AP_LightWareSerial — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct RangeFinderSample;

struct LightWareState {
  double distance_m{0.0};
  bool valid{false};
};

class VRP_LightWareSerial {
public:
  bool init();
  LightWareState update(const RangeFinderSample &rng, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_lightware(const LightWareState &s);

} // namespace vrp
