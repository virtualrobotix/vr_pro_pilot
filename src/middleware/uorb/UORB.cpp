#include "middleware/uorb/UORB.h"

namespace vrp {

void UORB::publish(const std::string &topic, const std::string &payload) {
  std::lock_guard<std::mutex> lk(mu_);
  bus_[topic] = payload;
}

std::optional<std::string> UORB::subscribe(const std::string &topic) const {
  std::lock_guard<std::mutex> lk(mu_);
  const auto it = bus_.find(topic);
  if (it == bus_.end()) {
    return std::nullopt;
  }
  return it->second;
}

} // namespace vrp
