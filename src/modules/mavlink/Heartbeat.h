#pragma once

#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class Heartbeat {
public:
  static std::string build(const std::string &vehicle, const std::string &mode, uint64_t t_ms,
                           bool armed = false);
  static std::string build_attitude(const Attitude &attitude, uint64_t t_ms);
  static std::string build_sys_status(bool armed, const BatteryStatus &battery, uint64_t t_ms);
};

} // namespace vrp
