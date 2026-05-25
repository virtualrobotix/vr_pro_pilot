#pragma once
/**
 * @module  libraries/VRP_TempCalibration
 * @dal     C
 * @req     VRP-LLRD-AP_TempCalibration
 * @parity  ArduPilot AP_TempCalibration — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct TempCalibrationState {
  float imu_offset_c{0.0F};
  float baro_offset_c{0.0F};
  bool calibrated{false};
};

class VRP_TempCalibration {
public:
  bool init();
  TempCalibrationState update(float throttle, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_temp_calibration(const TempCalibrationState &s);

} // namespace vrp
