#include "libraries/VRP_Gripper/VRP_Gripper.h"

#include <sstream>

namespace vrp {

bool VRP_Gripper::init() {
  state_ = GripperState::Open;
  return true;
}

GripperState VRP_Gripper::update(float command, bool armed) {
  if (!armed) {
    state_ = GripperState::Open;
    return state_;
  }
  if (command > 0.6F) {
    state_ = GripperState::Closed;
  } else if (command < 0.3F) {
    state_ = GripperState::Open;
  } else if (state_ == GripperState::Open) {
    state_ = GripperState::Closing;
  } else {
    state_ = GripperState::Opening;
  }
  return state_;
}

std::string format_gripper(GripperState s) {
  std::ostringstream oss;
  oss << "GRIPPER state=";
  switch (s) {
  case GripperState::Open:
    oss << "open";
    break;
  case GripperState::Closing:
    oss << "closing";
    break;
  case GripperState::Closed:
    oss << "closed";
    break;
  case GripperState::Opening:
    oss << "opening";
    break;
  }
  return oss.str();
}

} // namespace vrp
