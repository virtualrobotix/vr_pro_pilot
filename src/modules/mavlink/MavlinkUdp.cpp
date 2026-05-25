#include "modules/mavlink/MavlinkUdp.h"

#ifndef VRP_TARGET_CHIBIOS

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

namespace vrp {

bool MavlinkUdp::init(const std::string &host, uint16_t port) {
  fd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (fd_ < 0) {
    return false;
  }
  const int flags = fcntl(fd_, F_GETFL, 0);
  fcntl(fd_, F_SETFL, flags | O_NONBLOCK);

  sockaddr_in addr{};
  addr.sin_family = AF_INET;
  addr.sin_port = htons(port);
  if (::inet_pton(AF_INET, host.c_str(), &addr.sin_addr) != 1) {
    ::close(fd_);
    fd_ = -1;
    return false;
  }
  if (::connect(fd_, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) != 0) {
    ::close(fd_);
    fd_ = -1;
    return false;
  }
  return true;
}

void MavlinkUdp::close_socket() {
  if (fd_ >= 0) {
    ::close(fd_);
    fd_ = -1;
  }
}

bool MavlinkUdp::send(const std::vector<uint8_t> &frame) {
  if (fd_ < 0) {
    return false;
  }
  const ssize_t n = ::send(fd_, frame.data(), frame.size(), 0);
  return n == static_cast<ssize_t>(frame.size());
}

bool MavlinkUdp::recv_nonblock(std::vector<uint8_t> &frame) {
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

bool MavlinkUdp::init(const std::string &, uint16_t) { return false; }
void MavlinkUdp::close_socket() {}
bool MavlinkUdp::send(const std::vector<uint8_t> &) { return false; }
bool MavlinkUdp::recv_nonblock(std::vector<uint8_t> &) { return false; }

} // namespace vrp

#endif
