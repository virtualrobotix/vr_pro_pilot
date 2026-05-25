#pragma once
/**
 * @module  middleware/params/VRP_Param
 * @dal     B
 * @req     VRP-LLRD-AP_Param
 * @parity  ArduPilot AP_Param
 * @status  partial
 */

#include <cstddef>
#include <string>
#include <unordered_map>
#include <vector>

namespace vrp {

class VRPParamStore {
public:
  void seed_defaults();
  void set(const std::string &key, double value);
  double get(const std::string &key, double fallback = 0.0) const;
  size_t count() const { return order_.size(); }
  std::string name_at(size_t index) const;
  bool set_by_name(const std::string &name, double value);
  bool find_index(const std::string &name, uint16_t &index) const;

private:
  std::unordered_map<std::string, double> params_;
  std::vector<std::string> order_;
};

} // namespace vrp
