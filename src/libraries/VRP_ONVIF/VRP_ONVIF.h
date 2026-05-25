#pragma once
/**
 * @module  libraries/VRP_ONVIF
 * @dal     E
 * @req     VRP-LLRD-AP_ONVIF
 * @parity  ArduPilot AP_ONVIF — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct OnvifState {
  bool streaming{false};
  bool ptz_active{false};
  uint32_t clients{0};
};

class VRP_ONVIF {
public:
  bool init();
  OnvifState update(bool armed, bool gcs_link, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_onvif(const OnvifState &s);

} // namespace vrp
