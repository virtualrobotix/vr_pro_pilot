#pragma once
/**
 * @module  libraries/VRP_TemperatureSensor
 * @dal     C
 * @req     VRP-LLRD-AP_TemperatureSensor
 * @parity  ArduPilot AP_TemperatureSensor — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct TemperatureSample {
  double imu_c{0.0};
  double baro_c{0.0};
  bool valid{false};
};

class VRP_TemperatureSensor {
public:
  bool init();
  TemperatureSample update(float throttle, uint64_t tick);

private:
  double ambient_c_{22.0};
};

std::string format_temperature(const TemperatureSample &s);

} // namespace vrp
