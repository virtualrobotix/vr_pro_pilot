#pragma once
/**
 * @module  libraries/VRP_AC_Fence
 * @dal     B
 * @req     VRP-LLRD-AC_Fence
 * @parity  ArduPilot AC_Fence
 * @status  partial
 */
/**
 * @module  libraries/VRP_AC_Fence
 * @dal     B
 * @req     VRP-LLRD-AC_Fence
 */
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

enum class FenceStatus { Ok, Breach };

class VRP_AC_Fence {
public:
  bool init(double center_x, double center_y, double radius_m, double min_z, double max_z);
  FenceStatus check(const LocalPosition &pos, std::string &detail) const;

private:
  double cx_{0.0};
  double cy_{0.0};
  double radius_m_{100.0};
  double min_z_{-100.0};
  double max_z_{0.0};
};

} // namespace vrp
