#pragma once
/**
 * @module  libraries/VRP_Mission
 * @dal     B
 * @req     VRP-LLRD-AP_Mission
 * @parity  ArduPilot AP_Mission
 * @status  partial
 */
/**
 * @module  libraries/VRP_Mission
 * @dal     B
 * @req     VRP-LLRD-AP_Mission
 */
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

class VRP_Mission {
public:
  bool init(const std::vector<Waypoint> &waypoints, double acceptance_radius_m);
  std::string update(const LocalPosition &pos);

  void set_origin(double lat_deg, double lon_deg);
  void set_acceptance_radius(double acceptance_radius_m);
  void clear();
  bool add_item_int(int32_t lat_e7, int32_t lon_e7, float alt_m);
  bool get_item_int(size_t index, int32_t &lat_e7, int32_t &lon_e7, float &alt_m) const;
  Waypoint prev_target() const;
  void finalize_upload();
  size_t waypoint_count() const { return waypoints_.size(); }
  size_t current_index() const { return current_; }
  bool complete() const { return complete_; }
  bool has_active_target() const { return !complete_ && !waypoints_.empty(); }
  Waypoint active_target() const;
  const std::string &last_status() const { return last_status_; }
  int consume_reached_index();

private:
  std::vector<Waypoint> waypoints_{};
  double acceptance_radius_m_{2.0};
  double origin_lat_deg_{45.0};
  double origin_lon_deg_{9.0};
  size_t current_{0};
  bool complete_{false};
  int pending_reached_index_{-1};
  std::string last_status_{"MISSION idle"};
};

} // namespace vrp
