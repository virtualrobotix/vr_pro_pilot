#include "libraries/VRP_IOMCU/VRP_IOMCU.h"
#include <sstream>

namespace vrp {

bool VRP_IOMCU::init() { return true; }

IomcuState VRP_IOMCU::status(bool armed, uint64_t tick) {
  IomcuState out{};
  out.ok = armed || tick == 0;
  out.fw_ver = 42;
  return out;
}

std::string format_iomcu(const IomcuState &s) {
  std::ostringstream oss;
  oss << "IOMCU ok=" << (s.ok ? 1 : 0) << " ver=" << static_cast<int>(s.fw_ver);
  return oss.str();
}

} // namespace vrp
