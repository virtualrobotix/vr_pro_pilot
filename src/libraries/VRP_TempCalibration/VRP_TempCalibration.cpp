#include "libraries/VRP_TempCalibration/VRP_TempCalibration.h"

#include <sstream>

namespace vrp {

bool VRP_TempCalibration::init() {
  seq_ = 0;
  return true;
}

TempCalibrationState VRP_TempCalibration::update(float throttle, uint64_t tick) {
  TempCalibrationState out{};
  out.calibrated = tick >= 3;
  out.imu_offset_c = 2.5F + throttle * 0.5F;
  out.baro_offset_c = 1.0F + throttle * 0.3F;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_temp_calibration(const TempCalibrationState &s) {
  std::ostringstream oss;
  oss << "TEMPCAL cal=" << (s.calibrated ? 1 : 0) << " imu=" << s.imu_offset_c << " baro=" << s.baro_offset_c;
  return oss.str();
}

} // namespace vrp
