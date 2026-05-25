#pragma once
/**
 * @module  libraries/VRP_Torqeedo
 * @dal     C
 * @req     VRP-LLRD-AP_Torqeedo
 * @parity  ArduPilot AP_Torqeedo — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct TorqeedoState {
  uint16_t rpm{0};
  float power_w{0.0F};
  bool motor_on{false};
};

class VRP_Torqeedo {
public:
  bool init();
  TorqeedoState update(float throttle, bool armed, float voltage_v);

private:
  uint32_t seq_{0};
};

std::string format_torqeedo(const TorqeedoState &s);

} // namespace vrp
