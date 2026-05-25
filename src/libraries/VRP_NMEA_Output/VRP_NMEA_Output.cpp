#include "libraries/VRP_NMEA_Output/VRP_NMEA_Output.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <sstream>

namespace vrp {

bool VRP_NMEA_Output::init() {
  seq_ = 0;
  return true;
}

NmeaOutputState VRP_NMEA_Output::update(const GpsSample &gps, bool armed, uint64_t tick) {
  NmeaOutputState out{};
  out.active = armed && gps.valid;
  out.lat_deg = gps.lat_deg;
  out.lon_deg = gps.lon_deg;
  out.sentences = static_cast<uint32_t>(tick);
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_nmea_output(const NmeaOutputState &s) {
  std::ostringstream oss;
  oss << "NMEA active=" << (s.active ? 1 : 0) << " sent=" << s.sentences << " lat=" << s.lat_deg
      << " lon=" << s.lon_deg;
  return oss.str();
}

} // namespace vrp
