#pragma once
/** @module libraries/VRP_AC_InputManager @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct RcChannels;

struct InputManagerState {
  uint8_t mode_ch{0};
  bool valid{false};
};

class VRP_AC_InputManager {
public:
  bool init();
  InputManagerState update(const RcChannels &rc, bool armed);
  RcChannels apply_stabilize(const RcChannels &rc, double max_tilt_rad);
};

std::string format_input_manager(const InputManagerState &s);

} // namespace vrp
