#include "libraries/VRP_AR_Motors/VRP_AR_Motors.h"

#include <algorithm>
#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

namespace {
float slew_toward(float current, float target, float max_delta) {
  if (target > current + max_delta) {
    return current + max_delta;
  }
  if (target < current - max_delta) {
    return current - max_delta;
  }
  return target;
}
} // namespace

bool VRP_AR_Motors::init(ArFrameClass frame, bool skid_steering) {
  frame_ = frame;
  skid_steering_ = skid_steering;
  last_throttle_ = 0.0F;
  last_steering_ = 0.0F;
  slew_rate_ = frame == ArFrameClass::Boat ? 1.5F : 2.0F;
  return true;
}

ArMotorsState VRP_AR_Motors::update(float throttle, float steering, bool armed) {
  ArMotorsState out{};
  out.frame = frame_;
  out.active = armed;
  if (!armed) {
    last_throttle_ = 0.0F;
    last_steering_ = 0.0F;
    return out;
  }

  const float dt = 0.02F;
  const float max_delta = slew_rate_ * dt;
  const float thr = slew_toward(last_throttle_, VRP_Math::clamp(throttle, -0.5F, 1.0F), max_delta);
  const float steer = slew_toward(last_steering_, VRP_Math::clamp(steering, -1.0F, 1.0F), max_delta);
  last_throttle_ = thr;
  last_steering_ = steer;
  out.throttle = thr;
  out.steering = steer;

  if (skid_steering_) {
    out.left = VRP_Math::clamp(thr - steer * 0.5F, -0.5F, 1.0F);
    out.right = VRP_Math::clamp(thr + steer * 0.5F, -0.5F, 1.0F);
  } else {
    out.left = thr;
    out.right = steer;
  }
  return out;
}

std::string format_ar_motors(const ArMotorsState &s) {
  std::ostringstream oss;
  oss << "ARMOT active=" << (s.active ? 1 : 0) << " frame=" << static_cast<int>(s.frame) << " left=" << s.left
      << " right=" << s.right << " thr=" << s.throttle << " steer=" << s.steering;
  return oss.str();
}

} // namespace vrp
