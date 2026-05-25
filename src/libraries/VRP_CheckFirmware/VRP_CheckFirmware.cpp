#include "libraries/VRP_CheckFirmware/VRP_CheckFirmware.h"
#include <sstream>

namespace vrp {

bool VRP_CheckFirmware::init() { return true; }

CheckFirmwareState VRP_CheckFirmware::verify(uint64_t tick) {
  CheckFirmwareState out{};
  out.ok = true;
  out.crc = 0xDEADBEEFU ^ static_cast<uint32_t>(tick & 0xFF);
  return out;
}

std::string format_check_firmware(const CheckFirmwareState &s) {
  std::ostringstream oss;
  oss << "FWCHK ok=" << (s.ok ? 1 : 0) << " crc=0x" << std::hex << s.crc << std::dec;
  return oss.str();
}

} // namespace vrp
