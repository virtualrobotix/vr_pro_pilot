#pragma once
/** @module libraries/VRP_GyroFFT @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct GyroFftState {
  float peak_hz{0.0F};
  uint16_t bins{0};
  bool active{false};
};

class VRP_GyroFFT {
public:
  bool init();
  GyroFftState update(bool armed, float gyro_z, uint64_t tick);
};

std::string format_gyro_fft(const GyroFftState &s);

} // namespace vrp
