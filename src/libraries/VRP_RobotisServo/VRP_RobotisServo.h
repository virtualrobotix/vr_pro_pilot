#pragma once
/**
 * @module  libraries/VRP_RobotisServo
 * @dal     C
 * @req     VRP-LLRD-AP_RobotisServo
 * @parity  ArduPilot AP_RobotisServo — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct RobotisServoState {
  uint8_t id{0};
  float position_deg{0.0F};
  float torque_pct{0.0F};
  bool valid{false};
};

class VRP_RobotisServo {
public:
  bool init();
  RobotisServoState update(float command, float load, bool armed);

private:
  uint32_t seq_{0};
};

std::string format_robotis_servo(const RobotisServoState &s);

} // namespace vrp
