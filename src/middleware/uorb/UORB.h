#pragma once

#include <mutex>
#include <optional>
#include <string>
#include <unordered_map>

namespace vrp {

class UORB {
public:
  void publish(const std::string &topic, const std::string &payload);
  std::optional<std::string> subscribe(const std::string &topic) const;

private:
  mutable std::mutex mu_;
  std::unordered_map<std::string, std::string> bus_;
};

} // namespace vrp
