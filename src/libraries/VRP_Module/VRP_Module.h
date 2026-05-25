#pragma once
/** @module libraries/VRP_Module @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct ModuleState {
  uint32_t count{0};
};

class VRP_Module {
public:
  bool init();
  ModuleState update(uint64_t tick, bool armed);
};

std::string format_module(const ModuleState &s);

} // namespace vrp
