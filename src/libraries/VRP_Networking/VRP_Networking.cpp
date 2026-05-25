#include "libraries/VRP_Networking/VRP_Networking.h"

#include <sstream>

namespace vrp {

bool VRP_Networking::init() {
  tx_ = 0;
  return true;
}

NetworkStatus VRP_Networking::update(bool gcs_link, uint64_t tick) {
  NetworkStatus out{};
  out.link_up = gcs_link || tick > 2;
  out.address = out.link_up ? "192.168.1.10" : "0.0.0.0";
  tx_ += static_cast<uint32_t>(tick * 48U);
  out.tx_bytes = tx_;
  return out;
}

std::string format_network(const NetworkStatus &s) {
  std::ostringstream oss;
  oss << "NETWORK up=" << (s.link_up ? 1 : 0) << " ip=" << s.address << " tx=" << s.tx_bytes;
  return oss.str();
}

} // namespace vrp
