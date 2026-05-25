#pragma once
/**
 * @module  libraries/VRP_Logger
 * @dal     B
 * @req     VRP-LLRD-AP_Logger
 * @parity  ArduPilot AP_Logger
 * @status  partial
 */
/**
 * @module  libraries/VRP_Logger
 * @dal     B
 * @req     VRP-LLRD-AP_Logger
 */
#include <array>
#include <cstddef>
#include <cstdint>
#include <string>

namespace vrp {

class VRP_Logger {
public:
  static constexpr size_t kCapacity = 64;

  bool init();
  void write(uint64_t time_ms, const char *message);
  std::string summary() const;
  size_t count() const { return count_; }

private:
  struct Entry {
    uint64_t time_ms{0};
    char text[48]{};
  };

  std::array<Entry, kCapacity> ring_{};
  size_t head_{0};
  size_t count_{0};
};

} // namespace vrp
