#include "modules/mavlink/MavlinkUdpRx.h"

#ifndef VRP_TARGET_CHIBIOS

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace vrp {

bool MavlinkUdpRx::bind(uint16_t port) {
  fd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    return false;
  }
  int flags = fcntl(fd_, F_GETFL, 0);
  fcntl(fd_, F_SETFL, flags | O_NONBLOCK);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_addr.s_addr = htonl(INADDR_ANY);
  addr.sin_port = htons(port);
  if (::bind(fd_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0) {
    ::close(fd_);
    fd_ = -1;
    return false;
  }
  return true;
}

void MavlinkUdpRx::close_socket() {
  if (fd_ >= 0) {
    ::close(fd_);
    fd_ = -1;
  }
}

bool MavlinkUdpRx::recv_nonblock(std::vector<uint8_t> &frame) {
  if (fd_ < 0) {
    return false;
  }
  uint8_t buf[512];
  const ssize_t n = ::recv(fd_, buf, sizeof(buf), 0);
  if (n <= 0) {
    return false;
  }
  frame.assign(buf, buf + n);
  return true;
}

} // namespace vrp

#else

namespace vrp {

bool MavlinkUdpRx::bind(uint16_t) { return false; }
void MavlinkUdpRx::close_socket() {}
bool MavlinkUdpRx::recv_nonblock(std::vector<uint8_t> &) { return false; }

} // namespace vrp

#endif
