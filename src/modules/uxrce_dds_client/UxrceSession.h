#pragma once

#include <string>

#include "middleware/uorb/UORB.h"

namespace vrp {

class UxrceSession {
public:
  bool init(uint16_t agent_port = 8888);
  std::string tick(uint64_t time_ms, UORB &uorb);
  bool connected() const { return connected_; }

private:
  uint16_t port_{8888};
  uint32_t seq_{0};
  bool connected_{false};
  uint64_t connect_tick_{0};
};

} // namespace vrp
