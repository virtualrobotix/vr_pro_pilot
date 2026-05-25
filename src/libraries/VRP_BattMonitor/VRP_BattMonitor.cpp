#include "libraries/VRP_BattMonitor/VRP_BattMonitor.h"

namespace vrp {

bool VRP_BattMonitor::init(double min_voltage_v) {
  min_voltage_v_ = min_voltage_v;
  status_ = BatteryStatus{12.6, 100.0, true};
  return true;
}

BatteryStatus VRP_BattMonitor::update(uint64_t tick) {
  status_.voltage_v = 12.6 - static_cast<double>(tick) * 0.001;
  if (status_.voltage_v < min_voltage_v_) {
    status_.voltage_v = min_voltage_v_;
  }
  status_.remaining_pct = (status_.voltage_v - min_voltage_v_) / (12.6 - min_voltage_v_) * 100.0;
  status_.valid = status_.voltage_v >= min_voltage_v_;
  return status_;
}

} // namespace vrp
