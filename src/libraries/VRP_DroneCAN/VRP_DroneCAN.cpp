#include "libraries/VRP_DroneCAN/VRP_DroneCAN.h"

#include <cstring>
#include <sstream>

#include "libraries/VRP_CANManager/VRP_CANManager.h"

namespace vrp {

bool VRP_DroneCAN::init(uint8_t node_id) {
  node_id_ = node_id;
  tick_ = 0;
  esc_can_id_ = 0x01040000U | static_cast<uint32_t>(node_id_);
  return true;
}

std::string VRP_DroneCAN::heartbeat(uint64_t time_ms) {
  ++tick_;
  std::ostringstream oss;
  oss << "DRONECAN node=" << static_cast<int>(node_id_) << " tick=" << tick_ << " t_ms=" << time_ms;
  return oss.str();
}

std::string VRP_DroneCAN::esc_status(uint64_t time_ms, float throttle) {
  std::ostringstream oss;
  oss << "DRONECAN_ESC rpm=" << static_cast<int>(throttle * 10000.0F) << " t_ms=" << time_ms;
  return oss.str();
}

std::string VRP_DroneCAN::publish_esc(VRP_CANManager &can, float throttle) {
  uint8_t payload[8]{};
  const uint16_t rpm = static_cast<uint16_t>(throttle * 10000.0F);
  std::memcpy(payload, &rpm, 2);
  payload[2] = node_id_;
  const bool sent = can.send_frame(esc_can_id_, payload, 8);
  std::ostringstream oss;
  oss << "DRONECAN can_id=0x" << std::hex << esc_can_id_ << std::dec << " rpm=" << rpm << " sent=" << (sent ? 1 : 0);
  return oss.str();
}

} // namespace vrp
