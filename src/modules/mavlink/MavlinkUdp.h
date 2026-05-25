#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace vrp {

class MavlinkUdp {
public:
  bool init(const std::string &host, uint16_t port);
  void close_socket();
  bool send(const std::vector<uint8_t> &frame);
  bool recv_nonblock(std::vector<uint8_t> &frame);

private:
  int fd_{-1};
};

} // namespace vrp
