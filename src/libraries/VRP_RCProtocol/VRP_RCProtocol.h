#pragma once
/**
 * @module  libraries/VRP_RCProtocol
 * @dal     C
 * @req     VRP-LLRD-AP_RCProtocol
 * @parity  ArduPilot AP_RCProtocol
 * @status  partial
 */
/**
 * @module  libraries/VRP_RCProtocol
 * @dal     C
 * @req     VRP-LLRD-AP_RCProtocol
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_RCProtocol {
public:
  bool init();
  RcChannels update(uint64_t tick);

private:
  RcChannels last_{};
};

} // namespace vrp
