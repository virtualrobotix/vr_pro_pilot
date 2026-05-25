#include "libraries/VRP_TemperatureSensor/VRP_TemperatureSensor.h"

#include <sstream>

namespace vrp {

bool VRP_TemperatureSensor::init() {
  ambient_c_ = 22.0;
  return true;
}

TemperatureSample VRP_TemperatureSensor::update(float throttle, uint64_t tick) {
  TemperatureSample out{};
  out.imu_c = ambient_c_ + static_cast<double>(throttle) * 18.0 + static_cast<double>(tick) * 0.01;
  out.baro_c = ambient_c_ + 2.0;
  out.valid = true;
  return out;
}

std::string format_temperature(const TemperatureSample &s) {
  std::ostringstream oss;
  oss << "TEMP imu=" << s.imu_c << " baro=" << s.baro_c << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
