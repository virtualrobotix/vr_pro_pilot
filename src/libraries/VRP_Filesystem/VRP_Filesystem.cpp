#include "libraries/VRP_Filesystem/VRP_Filesystem.h"

#include <sstream>

namespace vrp {

bool VRP_Filesystem::init() {
  total_kb_ = 16384;
  used_kb_ = 256;
  return true;
}

FilesystemStatus VRP_Filesystem::status(uint64_t tick) const {
  FilesystemStatus out{};
  out.total_kb = total_kb_;
  out.free_kb = total_kb_ - used_kb_ - static_cast<uint32_t>(tick * 2U);
  out.mounted = true;
  return out;
}

std::string format_filesystem(const FilesystemStatus &s) {
  std::ostringstream oss;
  oss << "FS mounted=" << (s.mounted ? 1 : 0) << " total_kb=" << s.total_kb << " free_kb=" << s.free_kb;
  return oss.str();
}

} // namespace vrp
