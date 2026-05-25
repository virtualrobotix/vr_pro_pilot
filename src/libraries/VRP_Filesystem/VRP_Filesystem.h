#pragma once
/**
 * @module  libraries/VRP_Filesystem
 * @dal     C
 * @req     VRP-LLRD-AP_Filesystem
 * @parity  ArduPilot AP_Filesystem — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct FilesystemStatus {
  uint32_t total_kb{0};
  uint32_t free_kb{0};
  bool mounted{false};
};

class VRP_Filesystem {
public:
  bool init();
  FilesystemStatus status(uint64_t tick) const;

private:
  uint32_t total_kb_{16384};
  uint32_t used_kb_{0};
};

std::string format_filesystem(const FilesystemStatus &s);

} // namespace vrp
