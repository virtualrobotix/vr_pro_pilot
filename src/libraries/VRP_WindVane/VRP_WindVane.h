#pragma once
/**
 * @module  libraries/VRP_WindVane
 * @dal     C
 * @req     VRP-LLRD-AP_WindVane
 * @parity  ArduPilot AP_WindVane — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct WindSample {
  double speed_m_s{0.0};
  double direction_rad{0.0};
  bool valid{false};
};

class VRP_WindVane {
public:
  bool init();
  WindSample update(uint64_t tick);

private:
  double base_speed_{3.5};
};

std::string format_wind(const WindSample &s);

} // namespace vrp
