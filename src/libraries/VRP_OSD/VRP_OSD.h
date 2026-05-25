#pragma once
/**
 * @module  libraries/VRP_OSD
 * @dal     C
 * @req     VRP-LLRD-AP_OSD
 * @parity  ArduPilot AP_OSD
 * @status  partial
 */
/**
 * @module  libraries/VRP_OSD
 * @dal     C
 * @req     VRP-LLRD-AP_OSD
 */
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_OSD {
public:
  bool init();
  std::string render(const std::string &vehicle_mode, const LocalPosition &pos, const BatteryStatus &battery,
                     bool armed) const;
};

} // namespace vrp
