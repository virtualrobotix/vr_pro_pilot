#pragma once
/**
 * @module  libraries/VRP_RCMapper
 * @dal     C
 * @req     VRP-LLRD-AP_RCMapper
 * @parity  ArduPilot AP_RCMapper — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct RcChannels;

struct RcMapState {
  float roll{0.0F};
  float pitch{0.0F};
  float throttle{0.0F};
  float yaw{0.0F};
  bool valid{false};
};

class VRP_RCMapper {
public:
  bool init();
  RcMapState map(const RcChannels &rc);

private:
  uint32_t seq_{0};
};

std::string format_rc_map(const RcMapState &s);

} // namespace vrp
