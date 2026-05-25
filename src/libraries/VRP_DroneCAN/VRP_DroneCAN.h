#pragma once
/**
 * @module  libraries/VRP_DroneCAN
 * @dal     C
 * @req     VRP-LLRD-AP_DroneCAN
 * @parity  ArduPilot AP_DroneCAN
 * @status  partial
 */
/**
 * @module  libraries/VRP_DroneCAN
 * @dal     C
 * @req     VRP-LLRD-AP_DroneCAN
 */
#include <cstdint>
#include <string>

namespace vrp {

class VRP_CANManager;

class VRP_DroneCAN {
public:
  bool init(uint8_t node_id);
  std::string heartbeat(uint64_t time_ms);
  std::string esc_status(uint64_t time_ms, float throttle);
  std::string publish_esc(VRP_CANManager &can, float throttle);

private:
  uint8_t node_id_{127};
  uint32_t tick_{0};
  uint32_t esc_can_id_{0};
};

} // namespace vrp
