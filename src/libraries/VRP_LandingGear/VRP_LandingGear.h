#pragma once
/**
 * @module  libraries/VRP_LandingGear
 * @dal     B
 * @req     VRP-LLRD-AP_LandingGear
 * @parity  ArduPilot AP_LandingGear — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

enum class GearState { Retracted, Deploying, Deployed, Retracting };

class VRP_LandingGear {
public:
  bool init();
  GearState update(bool armed, bool land_mode);
  std::string status() const;

private:
  GearState state_{GearState::Retracted};
};

} // namespace vrp
