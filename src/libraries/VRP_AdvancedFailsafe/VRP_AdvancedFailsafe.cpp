#include "libraries/VRP_AdvancedFailsafe/VRP_AdvancedFailsafe.h"

#include <sstream>

namespace vrp {

bool VRP_AdvancedFailsafe::init(VRPParamStore &params) {
  low_batt_pct_ = params.get("failsafe.batt_rtl_pct", 20.0);
  gcs_timeout_ticks_ = static_cast<uint64_t>(params.get("failsafe.gcs_timeout_ticks", 125.0));
  test_force_rtl_ = params.get("failsafe.test_force_rtl", 0.0) > 0.5;
  rtl_requested_ = false;
  reason_ = "idle";
  return true;
}

void VRP_AdvancedFailsafe::note_gcs_link(uint64_t tick) { last_gcs_tick_ = tick; }

void VRP_AdvancedFailsafe::update(uint64_t tick, const BatteryStatus &battery, bool armed) {
  tick_ = tick;
  if (!armed) {
    rtl_requested_ = false;
    reason_ = "idle";
    return;
  }
  if (test_force_rtl_) {
    rtl_requested_ = true;
    reason_ = "test_force";
    return;
  }
  if (battery.remaining_pct <= low_batt_pct_) {
    rtl_requested_ = true;
    reason_ = "low_battery";
    return;
  }
  if (last_gcs_tick_ > 0 && tick > last_gcs_tick_ && (tick - last_gcs_tick_) > gcs_timeout_ticks_) {
    rtl_requested_ = true;
    reason_ = "gcs_timeout";
    return;
  }
  rtl_requested_ = false;
  reason_ = "ok";
}

bool VRP_AdvancedFailsafe::should_rtl() const { return rtl_requested_; }

bool VRP_AdvancedFailsafe::triggered() const { return rtl_requested_; }

std::string VRP_AdvancedFailsafe::status() const {
  std::ostringstream oss;
  oss << "FAILSAFE reason=" << reason_ << " rtl=" << (rtl_requested_ ? 1 : 0)
      << " gcs_age=" << (last_gcs_tick_ > 0 && tick_ >= last_gcs_tick_ ? tick_ - last_gcs_tick_ : 0);
  return oss.str();
}

} // namespace vrp
