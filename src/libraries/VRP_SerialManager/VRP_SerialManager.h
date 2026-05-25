#pragma once
/**
 * @module  libraries/VRP_SerialManager
 * @dal     C
 * @req     VRP-LLRD-AP_SerialManager
 * @parity  ArduPilot AP_SerialManager — clean-room BSD rewrite
 * @status  partial
 */
#include <array>
#include <cstdint>
#include <string>

namespace vrp {

class VRP_SerialManager {
public:
  bool init();
  std::array<uint8_t, 6> port_active_mask(uint64_t tick) const;

private:
  std::array<uint8_t, 6> ports_{};
};

std::string format_serial_ports(const std::array<uint8_t, 6> &ports);

} // namespace vrp
