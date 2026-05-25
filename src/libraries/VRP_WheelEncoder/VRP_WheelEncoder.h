#pragma once
/**
 * @module  libraries/VRP_WheelEncoder
 * @dal     C
 * @req     VRP-LLRD-AP_WheelEncoder
 * @parity  ArduPilot AP_WheelEncoder — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct WheelEncoderState {
  int32_t ticks{0};
  float speed_m_s{0.0F};
  bool valid{false};
};

class VRP_WheelEncoder {
public:
  bool init();
  WheelEncoderState update(double dx_m, double dy_m, bool armed);

private:
  int32_t ticks_{0};
};

std::string format_wheel_encoder(const WheelEncoderState &s);

} // namespace vrp
