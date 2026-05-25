#pragma once
/**
 * @module  libraries/VRP_RPM
 * @dal     E
 * @req     VRP-LLRD-AP_RPM
 * @parity  ArduPilot AP_RPM — clean-room BSD rewrite
 * @status  partial
 */
#include <array>
#include <string>

namespace vrp {

struct RpmSample {
  std::array<double, 4> rpm{{0.0, 0.0, 0.0, 0.0}};
  bool valid{false};
};

class VRP_RPM {
public:
  bool init();
  RpmSample update(float throttle);

private:
  double scale_{9800.0};
};

std::string format_rpm(const RpmSample &s);

} // namespace vrp
