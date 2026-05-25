#include "libraries/VRP_SmartRTL/VRP_SmartRTL.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_SmartRTL::init(size_t max_points, double min_step_m) {
  max_points_ = max_points;
  min_step_m_ = min_step_m;
  clear();
  return true;
}

void VRP_SmartRTL::clear() {
  path_.clear();
  rtl_active_ = false;
  rtl_index_ = 0;
  has_last_ = false;
}

void VRP_SmartRTL::update(const LocalPosition &pos, bool armed) {
  if (!armed || !pos.valid) {
    return;
  }
  if (!has_last_) {
    last_recorded_ = Waypoint{pos.x, pos.y, pos.z};
    path_.push_back(last_recorded_);
    has_last_ = true;
    return;
  }
  const double dx = pos.x - last_recorded_.x;
  const double dy = pos.y - last_recorded_.y;
  const double dist = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  if (dist < min_step_m_) {
    return;
  }
  last_recorded_ = Waypoint{pos.x, pos.y, pos.z};
  path_.push_back(last_recorded_);
  if (path_.size() > max_points_) {
    path_.erase(path_.begin());
  }
}

SmartRtlState VRP_SmartRTL::activate() {
  SmartRtlState state{};
  if (path_.empty()) {
    state.target = Waypoint{};
    return state;
  }
  rtl_active_ = true;
  rtl_index_ = path_.size() - 1;
  state.active = true;
  state.path_points = path_.size();
  state.rtl_index = rtl_index_;
  state.target = path_[rtl_index_];
  return state;
}

SmartRtlState VRP_SmartRTL::update_rtl(const LocalPosition &pos, double acceptance_radius_m) {
  SmartRtlState state{};
  if (!rtl_active_ || path_.empty() || !pos.valid) {
    return state;
  }
  state.active = true;
  state.path_points = path_.size();
  state.rtl_index = rtl_index_;
  state.target = path_[rtl_index_];

  const double dx = pos.x - state.target.x;
  const double dy = pos.y - state.target.y;
  const double dist = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  if (dist <= acceptance_radius_m && rtl_index_ > 0) {
    --rtl_index_;
    state.rtl_index = rtl_index_;
    state.target = path_[rtl_index_];
  }
  if (rtl_index_ == 0 && dist <= acceptance_radius_m) {
    state.complete = true;
    rtl_active_ = false;
  }
  return state;
}

std::string VRP_SmartRTL::status() const {
  std::ostringstream oss;
  oss << "SMART_RTL points=" << path_.size() << " active=" << (rtl_active_ ? 1 : 0) << " idx=" << rtl_index_;
  return oss.str();
}

std::string format_smart_rtl(const SmartRtlState &state) {
  std::ostringstream oss;
  oss << "SMART_RTL nav active=" << (state.active ? 1 : 0) << " pts=" << state.path_points
      << " idx=" << state.rtl_index << " tgt_x=" << state.target.x << " tgt_y=" << state.target.y
      << " complete=" << (state.complete ? 1 : 0);
  return oss.str();
}

} // namespace vrp
