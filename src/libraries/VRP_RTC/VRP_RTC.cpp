#include "libraries/VRP_RTC/VRP_RTC.h"

#include <sstream>

namespace vrp {

bool VRP_RTC::init() {
  boot_ms_ = 0;
  have_boot_ = false;
  return true;
}

std::string VRP_RTC::update(uint64_t time_ms) {
  if (!have_boot_) {
    boot_ms_ = time_ms;
    have_boot_ = true;
  }
  std::ostringstream oss;
  oss << "RTC utc_ms=" << (time_ms - boot_ms_) << " boot_ms=" << boot_ms_;
  return oss.str();
}

} // namespace vrp
