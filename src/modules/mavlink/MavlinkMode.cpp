#include "modules/mavlink/MavlinkMode.h"

namespace vrp {

std::string mavlink_mode_from_custom(const std::string &vehicle, uint32_t custom_mode) {
  if (vehicle == "boat") {
    switch (custom_mode) {
    case 0:
      return "Manual";
    case 10:
      return "Auto";
    case 11:
      return "RTL";
    default:
      return "Manual";
    }
  }
  if (vehicle == "vtol") {
    switch (custom_mode) {
    case 17:
      return "QStabilize";
    case 19:
      return "FW";
    case 6:
      return "RTL";
    default:
      return "QStabilize";
    }
  }
  if (vehicle == "subsea") {
    switch (custom_mode) {
    case 4:
      return "DepthHold";
    case 6:
      return "RTL";
    default:
      return "DepthHold";
    }
  }
  switch (custom_mode) {
  case 3:
    return "Auto";
  case 5:
    return "Loiter";
  case 6:
    return "RTL";
  case 2:
    return "AltHold";
  case 9:
    return "Land";
  default:
    return "Loiter";
  }
}

} // namespace vrp
