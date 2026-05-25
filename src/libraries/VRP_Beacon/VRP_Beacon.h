#pragma once
/**
 * @module  libraries/VRP_Beacon
 * @dal     C
 * @req     VRP-LLRD-AP_Beacon
 * @parity  ArduPilot AP_Beacon — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct BeaconSample {
  uint8_t id{0};
  double distance_m{0.0};
  double bearing_rad{0.0};
  bool valid{false};
};

class VRP_Beacon {
public:
  bool init();
  BeaconSample update(double own_x_m, double own_y_m);

private:
  double bx_{10.0};
  double by_{-5.0};
};

std::string format_beacon(const BeaconSample &s);

} // namespace vrp
