#pragma once
/**
 * @module  libraries/VRP_Airspeed
 * @dal     C
 * @req     VRP-LLRD-AP_Airspeed
 * @parity  ArduPilot AP_Airspeed — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct AirspeedSample {
  double speed_m_s{0.0};
  double differential_pa{0.0};
  bool valid{false};
};

class VRP_Airspeed {
public:
  bool init();
  AirspeedSample update(double ground_speed_m_s, uint64_t time_us);

private:
  double offset_m_s_{0.0};
};

std::string format_airspeed(const AirspeedSample &s);

} // namespace vrp
