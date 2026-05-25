#include "libraries/VRP_FlashIface/VRP_FlashIface.h"

#include <algorithm>
#include <sstream>

namespace vrp {

bool VRP_FlashIface::init() {
  geom_.sector_size = 16384;
  geom_.sector_count = 2;
  geom_.base_addr = 0x080E0000;
  backing_.assign(static_cast<size_t>(geom_.sector_size) * geom_.sector_count, 0xFF);
  return true;
}

bool VRP_FlashIface::read(uint32_t offset, uint8_t *buf, size_t len) const {
  if (buf == nullptr || offset + len > backing_.size()) {
    return false;
  }
  std::copy_n(backing_.begin() + offset, len, buf);
  return true;
}

bool VRP_FlashIface::write(uint32_t offset, const uint8_t *buf, size_t len) {
  if (buf == nullptr || offset + len > backing_.size()) {
    return false;
  }
  std::copy_n(buf, len, backing_.begin() + offset);
  return true;
}

bool VRP_FlashIface::erase_sector(uint32_t sector) {
  if (sector >= geom_.sector_count) {
    return false;
  }
  const size_t base = static_cast<size_t>(sector) * geom_.sector_size;
  std::fill(backing_.begin() + static_cast<std::ptrdiff_t>(base),
            backing_.begin() + static_cast<std::ptrdiff_t>(base + geom_.sector_size), 0xFF);
  return true;
}

std::string VRP_FlashIface::summary() const {
  std::ostringstream oss;
  oss << "FLASH base=0x" << std::hex << geom_.base_addr << std::dec << " sectors=" << geom_.sector_count
      << " size=" << geom_.sector_size;
  return oss.str();
}

} // namespace vrp
