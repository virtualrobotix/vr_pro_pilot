#include "libraries/VRP_Mission/VRP_Mission.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Mission::init(const std::vector<Waypoint> &waypoints, double acceptance_radius_m) {
  waypoints_ = waypoints;
  acceptance_radius_m_ = acceptance_radius_m;
  current_ = 0;
  complete_ = waypoints_.empty();
  last_status_ = complete_ ? "MISSION idle" : "MISSION loaded";
  return true;
}

Waypoint VRP_Mission::active_target() const {
  if (!has_active_target()) {
    return Waypoint{};
  }
  return waypoints_[current_];
}

std::string VRP_Mission::update(const LocalPosition &pos) {
  if (complete_ || waypoints_.empty() || !pos.valid) {
    last_status_ = "MISSION idle";
    return last_status_;
  }

  const Waypoint &wp = waypoints_[current_];
  const double dx = wp.x - pos.x;
  const double dy = wp.y - pos.y;
  const double dist = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));

  if (dist <= acceptance_radius_m_) {
    pending_reached_index_ = static_cast<int>(current_);
    if (current_ + 1 >= waypoints_.size()) {
      complete_ = true;
      last_status_ = "MISSION complete";
      return last_status_;
    }
    ++current_;
  }

  std::ostringstream oss;
  oss << "MISSION idx=" << current_ << " dist=" << dist << " target_x=" << waypoints_[current_].x
      << " target_y=" << waypoints_[current_].y;
  last_status_ = oss.str();
  return last_status_;
}

void VRP_Mission::clear() {
  waypoints_.clear();
  current_ = 0;
  complete_ = true;
}

bool VRP_Mission::add_item_int(int32_t lat_e7, int32_t lon_e7, float alt_m) {
  Waypoint wp{};
  wp.y = (static_cast<double>(lat_e7) / 1e7 - origin_lat_deg_) * 111320.0;
  wp.x = (static_cast<double>(lon_e7) / 1e7 - origin_lon_deg_) * 111320.0;
  wp.z = -static_cast<double>(alt_m);
  waypoints_.push_back(wp);
  complete_ = false;
  return true;
}

void VRP_Mission::finalize_upload() {
  current_ = 0;
  complete_ = waypoints_.empty();
}

bool VRP_Mission::get_item_int(size_t index, int32_t &lat_e7, int32_t &lon_e7, float &alt_m) const {
  if (index >= waypoints_.size()) {
    return false;
  }
  const Waypoint &wp = waypoints_[index];
  lat_e7 = static_cast<int32_t>((wp.y / 111320.0 + origin_lat_deg_) * 1e7);
  lon_e7 = static_cast<int32_t>((wp.x / 111320.0 + origin_lon_deg_) * 1e7);
  alt_m = static_cast<float>(-wp.z);
  return true;
}

Waypoint VRP_Mission::prev_target() const {
  if (waypoints_.empty() || current_ == 0) {
    return Waypoint{};
  }
  return waypoints_[current_ - 1];
}

int VRP_Mission::consume_reached_index() {
  const int idx = pending_reached_index_;
  pending_reached_index_ = -1;
  return idx;
}

} // namespace vrp
