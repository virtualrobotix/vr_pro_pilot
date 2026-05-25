#pragma once
/**
 * @module  libraries/VRP_InternalError
 * @dal     B
 * @req     VRP-LLRD-AP_InternalError
 * @parity  ArduPilot AP_InternalError — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct InternalErrorState {
  uint16_t code{0};
  uint32_t count{0};
  bool fault{false};
};

class VRP_InternalError {
public:
  bool init();
  InternalErrorState update(bool armed, uint64_t tick);

private:
  uint32_t count_{0};
};

std::string format_internal_error(const InternalErrorState &s);

} // namespace vrp
