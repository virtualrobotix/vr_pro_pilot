#include "libraries/VRP_WheelEncoder/VRP_WheelEncoder.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_WheelEncoder::init() {
  ticks_ = 0;
  return true;
}

WheelEncoderState VRP_WheelEncoder::update(double dx_m, double dy_m, bool armed) {
  WheelEncoderState out{};
  out.valid = armed;
  const double dist = std::sqrt(dx_m * dx_m + dy_m * dy_m);
  if (armed && dist > 0.001) {
    ticks_ += static_cast<int32_t>(dist * 100.0);
  }
  out.ticks = ticks_;
  out.speed_m_s = armed ? static_cast<float>(dist / 0.02) : 0.0F;
  return out;
}

std::string format_wheel_encoder(const WheelEncoderState &s) {
  std::ostringstream oss;
  oss << "WHEEL ticks=" << s.ticks << " speed=" << s.speed_m_s << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
