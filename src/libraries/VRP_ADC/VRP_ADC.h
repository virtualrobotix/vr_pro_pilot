#pragma once
/** @module libraries/VRP_ADC @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct BatteryStatus;

struct AdcState {
  uint8_t ch{0};
  float mv{0.0F};
};

class VRP_ADC {
public:
  bool init();
  AdcState update(const BatteryStatus &battery, bool armed);
};

std::string format_adc(const AdcState &s);

} // namespace vrp
