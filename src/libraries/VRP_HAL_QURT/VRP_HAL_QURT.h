#pragma once
/** @module libraries/VRP_HAL_QURT @dal     E @status  partial */
#include <string>

namespace vrp {

struct HalQurtState {
  bool ok{false};
  const char *backend{"qurt"};
};

class VRP_HAL_QURT {
public:
  bool init();
  HalQurtState status() const;

private:
  bool ok_{false};
};

std::string format_hal_qurt(const HalQurtState &s);

} // namespace vrp
