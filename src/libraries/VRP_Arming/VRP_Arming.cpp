#include "libraries/VRP_Arming/VRP_Arming.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_Arming::init(bool auto_arm_sitl) {
  auto_arm_sitl_ = auto_arm_sitl;
  state_ = ArmState::Disarmed;
  healthy_ticks_ = 0;
  arm_request_ = false;
  disarm_request_ = false;
  return true;
}

void VRP_Arming::request_arm() { arm_request_ = true; }

void VRP_Arming::request_disarm() {
  disarm_request_ = true;
  arm_request_ = false;
}

ArmState VRP_Arming::update(uint64_t tick, const ImuSample &imu, const BatteryStatus &battery,
                            const LocalPosition &pos) {
  if (disarm_request_) {
    state_ = ArmState::Disarmed;
    disarm_request_ = false;
    arm_request_ = false;
    return state_;
  }

  const bool imu_ok = std::isfinite(imu.az) && std::abs(imu.az) > 1.0;
  const bool batt_ok = battery.valid && battery.voltage_v >= 10.5;
  const bool pos_ok = pos.valid || tick < 3;

  if (imu_ok && batt_ok && pos_ok) {
    if (healthy_ticks_ < 1000) {
      ++healthy_ticks_;
    }
  } else {
    healthy_ticks_ = 0;
    state_ = ArmState::Disarmed;
    return state_;
  }

  if (arm_request_) {
    state_ = ArmState::Armed;
    arm_request_ = false;
    return state_;
  }

  if (state_ == ArmState::Disarmed && healthy_ticks_ >= 2) {
    state_ = ArmState::PreArm;
  }

  if (state_ == ArmState::PreArm && auto_arm_sitl_ && healthy_ticks_ >= 3) {
    state_ = ArmState::Armed;
  }

  (void)tick;
  return state_;
}

std::string VRP_Arming::status_text() const {
  std::ostringstream oss;
  switch (state_) {
  case ArmState::Disarmed:
    oss << "DISARMED";
    break;
  case ArmState::PreArm:
    oss << "PREARM";
    break;
  case ArmState::Armed:
    oss << "ARMED";
    break;
  }
  return oss.str();
}

} // namespace vrp
