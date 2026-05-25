#include "modules/mavlink/Heartbeat.h"

#include <sstream>

namespace vrp {

std::string Heartbeat::build(const std::string &vehicle, const std::string &mode, uint64_t t_ms, bool armed) {
  std::ostringstream oss;
  oss << "MAVLINK_HEARTBEAT vehicle=" << vehicle << " mode=" << mode << " armed=" << (armed ? 1 : 0)
      << " t_ms=" << t_ms << " udp=14550";
  return oss.str();
}

std::string Heartbeat::build_attitude(const Attitude &attitude, uint64_t t_ms) {
  std::ostringstream oss;
  oss << "MAVLINK_ATTITUDE roll=" << attitude.roll_rad << " pitch=" << attitude.pitch_rad
      << " yaw=" << attitude.yaw_rad << " t_ms=" << t_ms;
  return oss.str();
}

std::string Heartbeat::build_sys_status(bool armed, const BatteryStatus &battery, uint64_t t_ms) {
  std::ostringstream oss;
  oss << "MAVLINK_SYS_STATUS armed=" << (armed ? 1 : 0) << " batt_v=" << battery.voltage_v
      << " batt_pct=" << battery.remaining_pct << " t_ms=" << t_ms;
  return oss.str();
}

} // namespace vrp
