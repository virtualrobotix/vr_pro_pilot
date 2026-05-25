#pragma once
/**
 * @module  libraries/VRP_VideoTX
 * @dal     E
 * @req     VRP-LLRD-AP_VideoTX
 * @parity  ArduPilot AP_VideoTX — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct VideoTxState {
  uint16_t channel_mhz{5740};
  uint8_t power_mw{25};
  bool active{false};
};

class VRP_VideoTX {
public:
  bool init();
  VideoTxState update(bool armed, uint64_t tick);

private:
  uint16_t base_mhz_{5740};
};

std::string format_vtx(const VideoTxState &s);

} // namespace vrp
