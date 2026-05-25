#pragma once
/**
 * @module  libraries/VRP_PiccoloCAN
 * @dal     C
 * @req     VRP-LLRD-AP_PiccoloCAN
 * @parity  ArduPilot AP_PiccoloCAN — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct PiccoloCanState {
  bool bus_up{false};
  uint8_t nodes{0};
  uint32_t frames{0};
};

class VRP_PiccoloCAN {
public:
  bool init();
  PiccoloCanState update(bool armed, uint64_t tick);

private:
  uint32_t frames_{0};
};

std::string format_piccolo_can(const PiccoloCanState &s);

} // namespace vrp
