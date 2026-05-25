#include "libraries/VRP_RCProtocol/VRP_RCProtocol.h"

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_RCProtocol::init() {
  last_ = RcChannels{};
  last_.valid = true;
  return true;
}

RcChannels VRP_RCProtocol::update(uint64_t tick) {
  RcChannels rc{};
  rc.roll = 0.0F;
  rc.pitch = 0.0F;
  rc.throttle = 0.55F;
  rc.yaw = 0.0F;
  rc.aux1 = (tick > 2 && tick < 4) ? 0.85F : 0.1F;
  rc.aux2 = (tick >= 4) ? 0.9F : 0.1F;
  rc.aux3 = 0.1F;
  rc.aux4 = 0.1F;
  rc.valid = true;
  last_ = rc;
  (void)VRP_Math::clamp(static_cast<double>(tick), 0.0, 1000.0);
  return rc;
}

} // namespace vrp
