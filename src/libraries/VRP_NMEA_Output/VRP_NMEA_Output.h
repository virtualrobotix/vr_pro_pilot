#pragma once
/**
 * @module  libraries/VRP_NMEA_Output
 * @dal     C
 * @req     VRP-LLRD-AP_NMEA_Output
 * @parity  ArduPilot AP_NMEA_Output — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct GpsSample;

struct NmeaOutputState {
  uint32_t sentences{0};
  bool active{false};
  double lat_deg{0.0};
  double lon_deg{0.0};
};

class VRP_NMEA_Output {
public:
  bool init();
  NmeaOutputState update(const GpsSample &gps, bool armed, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_nmea_output(const NmeaOutputState &s);

} // namespace vrp
