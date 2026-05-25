#include "libraries/VRP_RC_Channel/VRP_RC_Channel.h"

namespace vrp {

bool VRP_RC_Channel::init() { return true; }

bool VRP_RC_Channel::aux_high(float v) { return v > 0.75F; }

std::string VRP_RC_Channel::mode_from_rc(const std::string &vehicle, const RcChannels &rc) const {
  if (!rc.valid) {
    return "Stabilize";
  }
  if (aux_high(rc.aux1)) {
    return "RTL";
  }
  if (aux_high(rc.aux2)) {
    return vehicle == "boat" ? "Auto" : "Auto";
  }
  if (aux_high(rc.aux3)) {
    return vehicle == "quad" ? "Acro" : "Manual";
  }
  if (rc.throttle < -0.5F && vehicle == "quad") {
    return "Land";
  }
  if (vehicle == "vtol") {
    return "QStabilize";
  }
  if (vehicle == "subsea") {
    return "DepthHold";
  }
  if (is_ar_surface_vehicle(vehicle)) {
    return "Manual";
  }
  return "Loiter";
}

} // namespace vrp
