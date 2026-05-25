#pragma once
/**
 * @module  libraries/VRP_Sailboat
 * @dal     B
 * @req     VRP-LLRD-Sailboat
 * @parity  ArduPilot Rover Sailboat mode — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_WindVane/VRP_WindVane.h"

namespace vrp {

struct SailboatOutput {
  float sail_sheet{0.0F};
  float rudder{0.0F};
  float throttle{0.0F};
  float steering{0.0F};
  bool active{false};
};

class VRP_Sailboat {
public:
  bool init(double max_speed_m_s = 4.0);
  SailboatOutput update(const Attitude &attitude, const WindSample &wind, float desired_turn_rate_rad_s,
                        float desired_speed_m_s, bool manual, float rc_sail, float rc_rudder, bool armed);

private:
  double max_speed_m_s_{4.0};
};

std::string format_sailboat(const SailboatOutput &s);

} // namespace vrp
