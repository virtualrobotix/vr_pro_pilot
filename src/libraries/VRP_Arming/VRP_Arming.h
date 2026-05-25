#pragma once
/**
 * @module  libraries/VRP_Arming
 * @dal     B
 * @req     VRP-LLRD-AP_Arming
 * @parity  ArduPilot AP_Arming
 * @status  partial
 */
/**
 * @module  libraries/VRP_Arming
 * @dal     B
 * @req     VRP-LLRD-AP_Arming
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

enum class ArmState { Disarmed, PreArm, Armed };

class VRP_Arming {
public:
  bool init(bool auto_arm_sitl);
  ArmState update(uint64_t tick, const ImuSample &imu, const BatteryStatus &battery, const LocalPosition &pos);

  void request_arm();
  void request_disarm();

  bool is_armed() const { return state_ == ArmState::Armed; }
  ArmState state() const { return state_; }
  std::string status_text() const;

private:
  bool auto_arm_sitl_{false};
  bool arm_request_{false};
  bool disarm_request_{false};
  ArmState state_{ArmState::Disarmed};
  uint32_t healthy_ticks_{0};
};

} // namespace vrp
