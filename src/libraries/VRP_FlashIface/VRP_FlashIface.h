#pragma once
/**
 * @module  libraries/VRP_FlashIface
 * @dal     C
 * @req     VRP-LLRD-AP_FlashIface
 * @parity  ArduPilot AP_FlashIface — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>
#include <vector>

namespace vrp {

struct FlashGeometry {
  uint32_t sector_size{16384};
  uint32_t sector_count{2};
  uint32_t base_addr{0x080E0000};
};

class VRP_FlashIface {
public:
  bool init();
  const FlashGeometry &geometry() const { return geom_; }
  bool read(uint32_t offset, uint8_t *buf, size_t len) const;
  bool write(uint32_t offset, const uint8_t *buf, size_t len);
  bool erase_sector(uint32_t sector);
  std::string summary() const;

private:
  FlashGeometry geom_{};
  std::vector<uint8_t> backing_{};
};

} // namespace vrp
