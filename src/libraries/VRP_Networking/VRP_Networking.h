#pragma once
/**
 * @module  libraries/VRP_Networking
 * @dal     C
 * @req     VRP-LLRD-AP_Networking
 * @parity  ArduPilot AP_Networking — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct NetworkStatus {
  bool link_up{false};
  std::string address{"0.0.0.0"};
  uint32_t tx_bytes{0};
};

class VRP_Networking {
public:
  bool init();
  NetworkStatus update(bool gcs_link, uint64_t tick);

private:
  uint32_t tx_{0};
};

std::string format_network(const NetworkStatus &s);

} // namespace vrp
