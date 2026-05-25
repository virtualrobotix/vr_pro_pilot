#pragma once
/**
 * @module  libraries/VRP_StorageManager
 * @dal     C
 * @req     VRP-LLRD-StorageManager
 * @parity  ArduPilot StorageManager — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct StorageManagerState {
  uint16_t blocks{0};
  uint16_t used{0};
  bool ready{false};
};

class VRP_StorageManager {
public:
  bool init();
  StorageManagerState status(uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_storage_manager(const StorageManagerState &s);

} // namespace vrp
