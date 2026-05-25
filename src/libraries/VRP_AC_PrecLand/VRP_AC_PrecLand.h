#pragma once
/**
 * @module  libraries/VRP_AC_PrecLand
 * @dal     B
 * @req     VRP-LLRD-AC_PrecLand
 * @parity  ArduPilot AC_PrecLand — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct RangeFinderSample;

struct PrecLandState {
  bool active{false};
  bool target_ok{false};
  double alt_m{0.0};
};

class VRP_AC_PrecLand {
public:
  bool init();
  PrecLandState update(const RangeFinderSample &rng, bool armed, const std::string &mode);

private:
  uint32_t seq_{0};
};

std::string format_prec_land(const PrecLandState &s);

} // namespace vrp
