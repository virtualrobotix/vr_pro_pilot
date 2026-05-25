#pragma once
/**
 * @module  libraries/VRP_AR_WPNav
 * @dal     B
 * @req     VRP-LLRD-AR_WPNav
 * @parity  ArduPilot AR_WPNav — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct LocalPosition;

struct ArWpNavState {
  uint16_t wp_index{0};
  double dist_m{0.0};
  bool active{false};
};

class VRP_AR_WPNav {
public:
  bool init();
  ArWpNavState update(const std::string &mode, const LocalPosition &pos, uint64_t tick);

private:
  uint16_t wp_{0};
};

std::string format_ar_wpnav(const ArWpNavState &s);

} // namespace vrp
