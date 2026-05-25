#pragma once
/**
 * @module  libraries/VRP_ServoRelayEvents
 * @dal     C
 * @req     VRP-LLRD-AP_ServoRelayEvents
 * @parity  ArduPilot AP_ServoRelayEvents — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct ServoRelayEventsState {
  uint8_t relay_mask{0};
  uint8_t servo_events{0};
  bool active{false};
};

class VRP_ServoRelayEvents {
public:
  bool init();
  ServoRelayEventsState update(bool armed, float throttle, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_servo_relay_events(const ServoRelayEventsState &s);

} // namespace vrp
