#pragma once
/**
 * @module  libraries/VRP_KDECAN
 * @dal     C
 * @req     VRP-LLRD-AP_KDECAN
 * @parity  ArduPilot AP_KDECAN — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct KdeCanState {
  uint8_t nodes{0};
  uint16_t rpm{0};
  bool bus_up{false};
};

class VRP_KDECAN {
public:
  bool init();
  KdeCanState update(float throttle, bool armed, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_kde_can(const KdeCanState &s);

} // namespace vrp
