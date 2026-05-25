#pragma once
/**
 * @module  libraries/VRP_AdvancedFailsafe
 * @dal     B
 * @req     VRP-LLRD-AP_AdvancedFailsafe
 * @parity  ArduPilot AP_AdvancedFailsafe — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"
#include "middleware/params/VRP_Param.h"

namespace vrp {

class VRP_AdvancedFailsafe {
public:
  bool init(VRPParamStore &params);
  void note_gcs_link(uint64_t tick);
  void update(uint64_t tick, const BatteryStatus &battery, bool armed);
  bool should_rtl() const;
  bool triggered() const;
  const std::string &reason() const { return reason_; }
  std::string status() const;

private:
  uint64_t last_gcs_tick_{0};
  uint64_t tick_{0};
  double low_batt_pct_{20.0};
  uint64_t gcs_timeout_ticks_{125};
  bool rtl_requested_{false};
  bool test_force_rtl_{false};
  std::string reason_{"idle"};
};

} // namespace vrp
