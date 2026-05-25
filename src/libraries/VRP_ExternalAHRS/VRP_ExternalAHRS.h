#pragma once
/**
 * @module  libraries/VRP_ExternalAHRS
 * @dal     B
 * @req     VRP-LLRD-AP_ExternalAHRS
 * @parity  ArduPilot AP_ExternalAHRS — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct Attitude;

struct ExternalAhrsState {
  double roll_deg{0.0};
  double pitch_deg{0.0};
  double yaw_deg{0.0};
  bool valid{false};
};

class VRP_ExternalAHRS {
public:
  bool init();
  ExternalAhrsState update(const Attitude &att, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_external_ahrs(const ExternalAhrsState &s);

} // namespace vrp
