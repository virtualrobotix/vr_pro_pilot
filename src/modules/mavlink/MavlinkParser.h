#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

namespace vrp {

struct MavlinkMessage {
  uint32_t msgid{0};
  std::vector<uint8_t> payload;
};

class MavlinkParser {
public:
  bool parse_v2(const uint8_t *data, size_t len, MavlinkMessage &out) const;
};

} // namespace vrp
