#include "libraries/VRP_Logger/VRP_Logger.h"

#include <cstring>
#include <sstream>

namespace vrp {

bool VRP_Logger::init() {
  head_ = 0;
  count_ = 0;
  ring_.fill(Entry{});
  return true;
}

void VRP_Logger::write(uint64_t time_ms, const char *message) {
  Entry &e = ring_[head_];
  e.time_ms = time_ms;
  std::strncpy(e.text, message, sizeof(e.text) - 1);
  e.text[sizeof(e.text) - 1] = '\0';
  head_ = (head_ + 1) % kCapacity;
  if (count_ < kCapacity) {
    ++count_;
  }
}

std::string VRP_Logger::summary() const {
  std::ostringstream oss;
  oss << "LOGGER entries=" << count_;
  if (count_ > 0) {
    const size_t idx = head_ == 0 ? kCapacity - 1 : head_ - 1;
    oss << " last=" << ring_[idx].text << "@" << ring_[idx].time_ms;
  }
  return oss.str();
}

} // namespace vrp
