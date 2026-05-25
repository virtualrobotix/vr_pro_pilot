#pragma once
/**
 * @module  libraries/VRP_RC_Channel
 * @dal     B
 * @req     VRP-LLRD-RC_Channel
 * @parity  ArduPilot RC_Channel
 * @status  partial
 */
/**
 * @module  libraries/VRP_RC_Channel
 * @dal     B
 * @req     VRP-LLRD-RC_Channel
 */
#include <string>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_RC_Channel {
public:
  bool init();
  std::string mode_from_rc(const std::string &vehicle, const RcChannels &rc) const;

private:
  static bool aux_high(float v);
};

} // namespace vrp
