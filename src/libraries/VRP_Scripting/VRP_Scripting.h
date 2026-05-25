#pragma once
/**
 * @module  libraries/VRP_Scripting
 * @dal     D
 * @req     VRP-LLRD-AP_Scripting
 * @parity  ArduPilot AP_Scripting
 * @status  partial
 */
/**
 * @module  libraries/VRP_Scripting
 * @dal     D
 * @req     VRP-LLRD-AP_Scripting
 */
#include <string>

namespace vrp {

class VRP_Scripting {
public:
  bool init(bool enable);
  std::string update(uint64_t tick, const std::string &current_mode);

private:
  bool enabled_{false};
};

} // namespace vrp
