#include "libraries/VRP_ServoRelayEvents/VRP_ServoRelayEvents.h"

#include <sstream>

namespace vrp {

bool VRP_ServoRelayEvents::init() {
  seq_ = 0;
  return true;
}

ServoRelayEventsState VRP_ServoRelayEvents::update(bool armed, float throttle, uint64_t tick) {
  ServoRelayEventsState out{};
  out.active = armed;
  out.relay_mask = armed ? 0x03 : 0;
  out.servo_events = armed ? static_cast<uint8_t>(throttle * 8.0F) : 0;
  ++seq_;
  (void)tick;
  (void)seq_;
  return out;
}

std::string format_servo_relay_events(const ServoRelayEventsState &s) {
  std::ostringstream oss;
  oss << "SRV_EVT active=" << (s.active ? 1 : 0) << " relay=" << static_cast<int>(s.relay_mask)
      << " servo=" << static_cast<int>(s.servo_events);
  return oss.str();
}

} // namespace vrp
