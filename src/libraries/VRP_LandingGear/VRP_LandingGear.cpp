#include "libraries/VRP_LandingGear/VRP_LandingGear.h"

#include <sstream>

namespace vrp {

bool VRP_LandingGear::init() {
  state_ = GearState::Retracted;
  return true;
}

GearState VRP_LandingGear::update(bool armed, bool land_mode) {
  if (land_mode) {
    state_ = GearState::Deployed;
  } else if (!armed) {
    state_ = GearState::Deployed;
  } else {
    state_ = GearState::Retracted;
  }
  return state_;
}

std::string VRP_LandingGear::status() const {
  std::ostringstream oss;
  switch (state_) {
  case GearState::Retracted:
    oss << "GEAR retracted";
    break;
  case GearState::Deploying:
    oss << "GEAR deploying";
    break;
  case GearState::Deployed:
    oss << "GEAR deployed";
    break;
  case GearState::Retracting:
    oss << "GEAR retracting";
    break;
  }
  return oss.str();
}

} // namespace vrp
