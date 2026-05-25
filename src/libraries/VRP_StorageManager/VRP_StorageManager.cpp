#include "libraries/VRP_StorageManager/VRP_StorageManager.h"

#include <sstream>

namespace vrp {

bool VRP_StorageManager::init() {
  seq_ = 0;
  return true;
}

StorageManagerState VRP_StorageManager::status(uint64_t tick) {
  StorageManagerState out{};
  out.ready = true;
  out.blocks = 128;
  out.used = static_cast<uint16_t>(32 + (tick % 16));
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_storage_manager(const StorageManagerState &s) {
  std::ostringstream oss;
  oss << "STORAGE ready=" << (s.ready ? 1 : 0) << " blocks=" << s.blocks << " used=" << s.used;
  return oss.str();
}

} // namespace vrp
