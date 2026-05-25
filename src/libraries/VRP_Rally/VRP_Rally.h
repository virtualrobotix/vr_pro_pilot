#pragma once
/**
 * @module  libraries/VRP_Rally
 * @dal     C
 * @req     VRP-LLRD-AP_Rally
 * @parity  ArduPilot AP_Rally — clean-room BSD rewrite
 * @status  partial
 */
#include <string>
#include <vector>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

struct RallyPoint {
  double x{0.0};
  double y{0.0};
  float alt_m{0.0F};
};

struct RallyStatus {
  size_t nearest_index{0};
  double distance_m{0.0};
  bool valid{false};
};

class VRP_Rally {
public:
  bool init();
  RallyStatus nearest(const LocalPosition &pos) const;

private:
  std::vector<RallyPoint> points_{};
};

std::string format_rally(const RallyStatus &s);

} // namespace vrp
