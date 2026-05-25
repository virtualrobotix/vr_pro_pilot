#pragma once
/**
 * @module  libraries/VRP_CANManager
 * @dal     C
 * @req     VRP-LLRD-AP_CANManager
 * @parity  ArduPilot AP_CANManager
 * @status  partial
 */
/**
 * @module  libraries/VRP_CANManager
 * @dal     C
 * @req     VRP-LLRD-AP_CANManager
 */
#include <cstdint>
#include <string>

namespace vrp {

class VRP_CANManager {
public:
  bool init();
  bool send_frame(uint32_t can_id, const uint8_t *data, uint8_t dlc);
  std::string status() const;

  uint32_t frames() const { return frames_; }
  uint32_t last_id() const { return last_id_; }

private:
  bool ready_{false};
  uint32_t frames_{0};
  uint32_t last_id_{0};
};

} // namespace vrp
