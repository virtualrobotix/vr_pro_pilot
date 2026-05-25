#pragma once
/** @module libraries/VRP_IOMCU @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct IomcuState {
  bool ok{false};
  uint8_t fw_ver{0};
};

class VRP_IOMCU {
public:
  bool init();
  IomcuState status(bool armed, uint64_t tick);
};

std::string format_iomcu(const IomcuState &s);

} // namespace vrp
