#pragma once
/**
 * @module  libraries/VRP_FlashStorage
 * @dal     C
 * @req     VRP-LLRD-AP_FlashStorage
 * @parity  ArduPilot AP_FlashStorage — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

#include "libraries/VRP_FlashIface/VRP_FlashIface.h"
#include "middleware/params/VRP_Param.h"

namespace vrp {

class VRP_FlashStorage {
public:
  bool init(VRP_FlashIface &iface);
  bool load(VRPParamStore &params);
  bool save(const VRPParamStore &params);
  std::string status() const;

private:
  VRP_FlashIface *iface_{nullptr};
  bool dirty_{false};
  std::string last_op_{"idle"};
};

} // namespace vrp
