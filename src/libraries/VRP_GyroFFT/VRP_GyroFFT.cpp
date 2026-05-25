#include "libraries/VRP_GyroFFT/VRP_GyroFFT.h"
#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_GyroFFT::init() { return true; }

GyroFftState VRP_GyroFFT::update(bool armed, float gyro_z, uint64_t tick) {
  GyroFftState out{};
  out.active = armed;
  out.bins = armed ? 128 : 0;
  out.peak_hz = armed ? std::fabs(gyro_z) * 10.0F + static_cast<float>(tick % 20) : 0.0F;
  return out;
}

std::string format_gyro_fft(const GyroFftState &s) {
  std::ostringstream oss;
  oss << "GYROFFT active=" << (s.active ? 1 : 0) << " peak=" << s.peak_hz << " bins=" << s.bins;
  return oss.str();
}

} // namespace vrp
