#pragma once

#include <cstdint>
#include <vector>

namespace vrp {

class MavlinkUdpRx {
public:
  bool bind(uint16_t port);
  void close_socket();
  bool recv_nonblock(std::vector<uint8_t> &frame);

private:
  int fd_{-1};
};

} // namespace vrp
