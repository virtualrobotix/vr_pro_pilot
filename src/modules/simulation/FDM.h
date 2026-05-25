#pragma once
/**
 * @module  modules/simulation/FDM
 * @dal     C
 * @req     VRP-LLRD-SITL
 * @parity  ArduPilot SITL
 * @status  partial
 */

#include <string>

namespace vrp {

struct FDMState {
  double x{0.0};
  double y{0.0};
  double z{0.0};
  double yaw_deg{0.0};
  double roll_deg{0.0};
  double pitch_deg{0.0};
  double ax{0.0};
  double ay{0.0};
  double az{-9.80665};
  double gx{0.0};
  double gy{0.0};
  double gz{0.0};
};

class FDM {
public:
  explicit FDM(std::string model) : model_(std::move(model)) {}
  void step(const std::string &vehicle, double dt_s, FDMState &state) const;

private:
  std::string model_;
};

} // namespace vrp
