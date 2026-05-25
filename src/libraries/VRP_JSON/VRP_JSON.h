#pragma once
/** @module libraries/VRP_JSON @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct JsonState {
  uint32_t keys{0};
};

class VRP_JSON {
public:
  bool init();
  JsonState update(uint64_t tick, bool armed);
};

std::string format_json(const JsonState &s);

} // namespace vrp
