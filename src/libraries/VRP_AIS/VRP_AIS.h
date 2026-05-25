#pragma once
/**
 * @module  libraries/VRP_AIS
 * @dal     C
 * @req     VRP-LLRD-AP_AIS
 * @parity  ArduPilot AP_AIS — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct AisVessel {
  uint32_t mmsi{0};
  double distance_m{0.0};
  double cog_rad{0.0};
  double sog_m_s{0.0};
  bool valid{false};
};

class VRP_AIS {
public:
  bool init();
  AisVessel update(uint64_t tick, double own_x_m, double own_y_m);

private:
  double base_x_{80.0};
  double base_y_{-20.0};
};

std::string format_ais(const AisVessel &v);

} // namespace vrp
