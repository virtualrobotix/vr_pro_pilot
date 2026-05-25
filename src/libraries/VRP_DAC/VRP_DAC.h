#pragma once
/** @module libraries/VRP_DAC @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct DacState {
  uint8_t ch{0};
  float val{0.0F};
};

class VRP_DAC {
public:
  bool init();
  DacState update(float throttle, bool armed);
};

std::string format_dac(const DacState &s);

} // namespace vrp
