#pragma once
/**
 * @module  libraries/VRP_Gripper
 * @dal     C
 * @req     VRP-LLRD-AP_Gripper
 * @parity  ArduPilot AP_Gripper — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

enum class GripperState { Open, Closing, Closed, Opening };

class VRP_Gripper {
public:
  bool init();
  GripperState update(float command, bool armed);

private:
  GripperState state_{GripperState::Open};
};

std::string format_gripper(GripperState s);

} // namespace vrp
