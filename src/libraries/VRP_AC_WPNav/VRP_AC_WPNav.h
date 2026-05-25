#pragma once
/**
 * @module  libraries/VRP_AC_WPNav
 * @dal     B
 * @req     VRP-LLRD-AC_WPNav
 * @parity  ArduPilot AC_WPNav
 * @status  partial
 */
/**
 * @module  libraries/VRP_AC_WPNav
 * @dal     B
 * @req     VRP-LLRD-AC_WPNav
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_AC_WPNav {
public:
  bool init(double cruise_speed_m_s);
  WpNavOutput update(const LocalPosition &pos, const Waypoint &target);

private:
  double cruise_speed_m_s_{2.0};
};

} // namespace vrp
