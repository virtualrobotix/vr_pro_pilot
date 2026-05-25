#pragma once
/** @module libraries/VRP_AccelCal @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct AccelCalState {
  uint8_t step{0};
  bool running{false};
};

class VRP_AccelCal {
public:
  bool init();
  AccelCalState update(bool armed, uint64_t tick);
};

std::string format_accel_cal(const AccelCalState &s);

} // namespace vrp
