#pragma once
/**
 * @module  libraries/VRP_Mount
 * @dal     C
 * @req     VRP-LLRD-AP_Mount
 * @parity  ArduPilot AP_Mount — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

struct MountState {
  double yaw_deg{0.0};
  double pitch_deg{0.0};
  bool active{false};
};

class VRP_Mount {
public:
  bool init();
  MountState update(const Attitude &att, bool armed);

private:
  double neutral_pitch_{-45.0};
};

std::string format_mount(const MountState &s);

} // namespace vrp
