#include "modules/uxrce_dds_client/UxrceSession.h"

#include <sstream>

namespace vrp {

bool UxrceSession::init(uint16_t agent_port) {
  port_ = agent_port;
  seq_ = 0;
  connected_ = false;
  connect_tick_ = 0;
  return true;
}

std::string UxrceSession::tick(uint64_t time_ms, UORB &uorb) {
  ++seq_;
  if (!connected_ && seq_ >= 2) {
    connected_ = true;
    connect_tick_ = time_ms;
  }
  const std::string status = connected_ ? "connected" : "waiting";
  uorb.publish("/uxrce/session", "port=" + std::to_string(port_) + " status=" + status);
  std::ostringstream oss;
  oss << "UXRCE port=" << port_ << " status=" << status << " seq=" << seq_;
  if (connected_) {
    oss << " agent_ms=" << connect_tick_;
  }
  return oss.str();
}

} // namespace vrp
