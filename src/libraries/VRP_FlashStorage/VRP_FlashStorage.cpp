#include "libraries/VRP_FlashStorage/VRP_FlashStorage.h"

#include <cstring>
#include <sstream>

namespace vrp {

namespace {
constexpr char kMagic[4] = {'V', 'R', 'P', 'P'};
constexpr uint32_t kMaxEntries = 32;
constexpr uint32_t kNameMax = 32;
} // namespace

bool VRP_FlashStorage::init(VRP_FlashIface &iface) {
  iface_ = &iface;
  dirty_ = false;
  last_op_ = "init";
  return iface_->init();
}

bool VRP_FlashStorage::load(VRPParamStore &params) {
  if (iface_ == nullptr) {
    return false;
  }
  uint8_t header[8]{};
  if (!iface_->read(0, header, sizeof(header))) {
    last_op_ = "load_fail";
    return false;
  }
  if (std::memcmp(header, kMagic, 4) != 0) {
    last_op_ = "load_empty";
    return true;
  }
  uint32_t count = 0;
  std::memcpy(&count, header + 4, 4);
  count = std::min(count, kMaxEntries);
  uint32_t offset = 8;
  for (uint32_t i = 0; i < count; ++i) {
    char name[kNameMax + 1]{};
    if (!iface_->read(offset, reinterpret_cast<uint8_t *>(name), kNameMax)) {
      last_op_ = "load_fail";
      return false;
    }
    offset += kNameMax;
    double value = 0.0;
    if (!iface_->read(offset, reinterpret_cast<uint8_t *>(&value), sizeof(value))) {
      last_op_ = "load_fail";
      return false;
    }
    offset += static_cast<uint32_t>(sizeof(value));
    if (name[0] != '\0') {
      params.set_by_name(name, value);
    }
  }
  last_op_ = "loaded";
  dirty_ = false;
  return true;
}

bool VRP_FlashStorage::save(const VRPParamStore &params) {
  if (iface_ == nullptr) {
    return false;
  }
  if (!iface_->erase_sector(0)) {
    last_op_ = "save_fail";
    return false;
  }
  const uint32_t count = static_cast<uint32_t>(std::min(params.count(), static_cast<size_t>(kMaxEntries)));
  uint8_t header[8]{};
  std::memcpy(header, kMagic, 4);
  std::memcpy(header + 4, &count, 4);
  if (!iface_->write(0, header, sizeof(header))) {
    last_op_ = "save_fail";
    return false;
  }
  uint32_t offset = 8;
  for (uint32_t i = 0; i < count; ++i) {
    const std::string name = params.name_at(i);
    char name_buf[kNameMax + 1]{};
    std::strncpy(name_buf, name.c_str(), kNameMax);
    if (!iface_->write(offset, reinterpret_cast<const uint8_t *>(name_buf), kNameMax)) {
      last_op_ = "save_fail";
      return false;
    }
    offset += kNameMax;
    const double value = params.get(name, 0.0);
    if (!iface_->write(offset, reinterpret_cast<const uint8_t *>(&value), sizeof(value))) {
      last_op_ = "save_fail";
      return false;
    }
    offset += static_cast<uint32_t>(sizeof(value));
  }
  dirty_ = false;
  last_op_ = "saved";
  return true;
}

std::string VRP_FlashStorage::status() const {
  std::ostringstream oss;
  oss << "FLASH_STORAGE op=" << last_op_ << " dirty=" << (dirty_ ? 1 : 0);
  return oss.str();
}

} // namespace vrp
