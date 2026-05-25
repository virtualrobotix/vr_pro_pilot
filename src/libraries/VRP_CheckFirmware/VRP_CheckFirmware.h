#pragma once
/** @module libraries/VRP_CheckFirmware @dal     B @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct CheckFirmwareState {
  bool ok{false};
  uint32_t crc{0};
};

class VRP_CheckFirmware {
public:
  bool init();
  CheckFirmwareState verify(uint64_t tick);
};

std::string format_check_firmware(const CheckFirmwareState &s);

} // namespace vrp
