#include "libraries/VRP_ROMFS/VRP_ROMFS.h"

#include <sstream>

namespace vrp {

bool VRP_ROMFS::init() {
  seq_ = 0;
  return true;
}

RomfsState VRP_ROMFS::status(uint64_t tick) {
  RomfsState out{};
  out.mounted = true;
  out.files = 12;
  out.size_kb = 256 + static_cast<uint32_t>(tick % 16);
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_romfs(const RomfsState &s) {
  std::ostringstream oss;
  oss << "ROMFS mounted=" << (s.mounted ? 1 : 0) << " files=" << s.files << " size_kb=" << s.size_kb;
  return oss.str();
}

} // namespace vrp
