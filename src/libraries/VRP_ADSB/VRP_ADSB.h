#pragma once
/**
 * @module  libraries/VRP_ADSB
 * @dal     C
 * @req     VRP-LLRD-AP_ADSB
 * @parity  ArduPilot AP_ADSB — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

enum class AdsbThreat { Safe, Warn, Critical };

struct AdsbVehicle {
  int32_t lat_e7{0};
  int32_t lon_e7{0};
  int32_t alt_mm{0};
  uint16_t heading_cdeg{0};
  uint16_t squawk{0};
  uint32_t icao{0};
  double distance_m{0.0};
  double vertical_sep_m{0.0};
  AdsbThreat threat{AdsbThreat::Safe};
  bool valid{false};
};

class VRP_ADSB {
public:
  bool init(double intruder_x_m = 120.0);
  void set_intruder_x(double x_m);
  AdsbVehicle update(uint64_t tick, double own_x_m, double own_y_m, double own_alt_m = 0.0);

private:
  double base_x_{120.0};
  double base_y_{0.0};
  AdsbThreat classify(double distance_m) const;
};

std::string format_adsb(const AdsbVehicle &v);
const char *adsb_threat_name(AdsbThreat t);

} // namespace vrp
