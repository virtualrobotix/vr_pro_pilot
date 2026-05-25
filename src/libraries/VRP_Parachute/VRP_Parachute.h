#pragma once
/**
 * @module  libraries/VRP_Parachute
 * @dal     B
 * @req     VRP-LLRD-AP_Parachute
 * @parity  ArduPilot AP_Parachute — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

class VRP_Parachute {
public:
  bool init();
  bool update(bool deploy_request, double alt_m);
  bool deployed() const { return deployed_; }

private:
  bool deployed_{false};
  bool released_{false};
};

std::string format_parachute(bool deployed, bool released);

} // namespace vrp
