#include "libraries/VRP_AR_Motors/VRP_AR_Motors.h"

#include <algorithm>
#include <sstream>

namespace vrp {

bool VRP_AR_Motors::init() {
  seq_ = 0;
  return true;
}

ArMotorsState VRP_AR_Motors::update(float throttle, float steer, bool armed) {
  ArMotorsState out{};
  out.active = armed;
  const float t = std::max(0.0F, throttle);
  out.left = armed ? std::max(0.0F, t - steer * 0.5F) : 0.0F;
  out.right = armed ? std::max(0.0F, t + steer * 0.5F) : 0.0F;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_ar_motors(const ArMotorsState &s) {
  std::ostringstream oss;
  oss << "ARMOT active=" << (s.active ? 1 : 0) << " left=" << s.left << " right=" << s.right;
  return oss.str();
}

} // namespace vrp
