#include "middleware/params/VRP_Param.h"

namespace vrp {

void VRPParamStore::seed_defaults() {
  params_.clear();
  order_.clear();
  set("ARMING_CHECK", 1.0);
  set("NAV_SPEED", 2.0);
  set("RTL_ALT", 20.0);
  set("system.auto_arm_sitl", 1.0);
  set("failsafe.batt_rtl_pct", 20.0);
}

void VRPParamStore::set(const std::string &key, double value) {
  if (params_.find(key) == params_.end()) {
    order_.push_back(key);
  }
  params_[key] = value;
}

double VRPParamStore::get(const std::string &key, double fallback) const {
  const auto it = params_.find(key);
  if (it == params_.end()) {
    return fallback;
  }
  return it->second;
}

std::string VRPParamStore::name_at(size_t index) const {
  if (index >= order_.size()) {
    return {};
  }
  return order_[index];
}

bool VRPParamStore::set_by_name(const std::string &name, double value) {
  if (params_.find(name) == params_.end()) {
    order_.push_back(name);
  }
  params_[name] = value;
  return true;
}

bool VRPParamStore::find_index(const std::string &name, uint16_t &index) const {
  for (size_t i = 0; i < order_.size(); ++i) {
    if (order_[i] == name) {
      index = static_cast<uint16_t>(i);
      return true;
    }
  }
  return false;
}

} // namespace vrp
