#include "libraries/VRP_IRLock/VRP_IRLock.h"

#include <sstream>

namespace vrp {

bool VRP_IRLock::init() {
  seq_ = 0;
  return true;
}

IRLockState VRP_IRLock::update(bool armed, double pos_x, double pos_y, uint64_t tick) {
  IRLockState out{};
  out.target_valid = armed && tick >= 2;
  out.x_m = static_cast<float>(pos_x * 0.01);
  out.y_m = static_cast<float>(pos_y * 0.01);
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_irlock(const IRLockState &s) {
  std::ostringstream oss;
  oss << "IRLOCK x=" << s.x_m << " y=" << s.y_m << " valid=" << (s.target_valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
