#pragma once
/**
 * @module  libraries/VRP_AC_Avoidance
 * @dal     C
 * @req     VRP-LLRD-AC_Avoidance
 * @parity  ArduPilot AC_Avoidance — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

#include "libraries/VRP_ADSB/VRP_ADSB.h"
#include "libraries/VRP_Proximity/VRP_Proximity.h"

namespace vrp {

struct AvoidanceOutput {
  bool active{false};
  double bearing_rad{0.0};
  double speed_m_s{0.0};
  std::string source{"none"};
};

class VRP_AC_Avoidance {
public:
  bool init(double warn_m = 80.0, double critical_m = 30.0);
  AvoidanceOutput update(const AdsbVehicle &adsb, const ProximitySample &prox);

private:
  double warn_m_{80.0};
  double critical_m_{30.0};
};

std::string format_avoidance(const AvoidanceOutput &o);

} // namespace vrp
