#include "libraries/VRP_CANManager/VRP_CANManager.h"

#include <sstream>

namespace vrp {

bool VRP_CANManager::init() {
  ready_ = true;
  frames_ = 0;
  last_id_ = 0;
  return true;
}

bool VRP_CANManager::send_frame(uint32_t can_id, const uint8_t *data, uint8_t dlc) {
  (void)data;
  if (!ready_ || dlc == 0) {
    return false;
  }
  ++frames_;
  last_id_ = can_id;
  return true;
}

std::string VRP_CANManager::status() const {
  std::ostringstream oss;
  oss << "CAN manager ready=" << (ready_ ? 1 : 0) << " frames=" << frames_ << " last_id=0x" << std::hex << last_id_
      << std::dec;
  return oss.str();
}

} // namespace vrp
