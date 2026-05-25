#include "libraries/VRP_RAMTRON/VRP_RAMTRON.h"

#include <sstream>

namespace vrp {

bool VRP_RAMTRON::init() {
  seq_ = 0;
  return true;
}

RamtronState VRP_RAMTRON::status(uint64_t tick) {
  RamtronState out{};
  out.ok = true;
  out.base_addr = 0x080F0000U;
  out.size_kb = 64;
  ++seq_;
  (void)tick;
  (void)seq_;
  return out;
}

std::string format_ramtron(const RamtronState &s) {
  std::ostringstream oss;
  oss << "RAMTRON ok=" << (s.ok ? 1 : 0) << " base=0x" << std::hex << s.base_addr << std::dec
      << " kb=" << s.size_kb;
  return oss.str();
}

} // namespace vrp
