#include "modules/mavlink/MavlinkMode.h"

namespace vrp {

std::string mavlink_mode_from_custom(const std::string &vehicle, uint32_t custom_mode) {
  if (vehicle == "boat" || vehicle == "sailboat" || vehicle == "rover") {
    switch (custom_mode) {
    case 0:
      return "Manual";
    case 1:
      return "Steering";
    case 4:
      return "Hold";
    case 5:
      return "Loiter";
    case 10:
      return "Auto";
    case 11:
      return "RTL";
    case 15:
      return "Guided";
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
  case 4:
    return "Guided";
  case 9:
    return "Land";
  default:
    return "Loiter";
  }
}

uint32_t mavlink_custom_mode_from_mode(const std::string &vehicle, const std::string &mode) {
  if (vehicle == "boat" || vehicle == "sailboat" || vehicle == "rover") {
    if (mode == "Manual") {
      return 0U;
    }
    if (mode == "Loiter") {
      return 5U;
    }
    if (mode == "Auto") {
      return 10U;
    }
    if (mode == "RTL") {
      return 11U;
    }
    if (mode == "Guided") {
      return 15U;
    }
    if (mode == "Steering") {
      return 1U;
    }
    if (mode == "Hold") {
      return 4U;
    }
    return 0U;
  }
  if (vehicle == "vtol") {
    if (mode == "FW") {
      return 19U;
    }
    if (mode == "RTL") {
      return 6U;
    }
    return 17U;
  }
  if (vehicle == "subsea") {
    if (mode == "RTL") {
      return 6U;
    }
    return 4U;
  }
  if (mode == "Auto") {
    return 3U;
  }
  if (mode == "Loiter") {
    return 5U;
  }
  if (mode == "RTL") {
    return 6U;
  }
  if (mode == "Land") {
    return 9U;
  }
  if (mode == "Guided") {
    return 4U;
  }
  if (mode == "AltHold") {
    return 2U;
  }
  return 5U;
}

} // namespace vrp
