#pragma once

#include <string>

#include "libraries/VRP_AC_Fence/VRP_AC_Fence.h"
#include "libraries/VRP_AC_Avoidance/VRP_AC_Avoidance.h"
#include "libraries/VRP_AdvancedFailsafe/VRP_AdvancedFailsafe.h"
#include "libraries/VRP_Arming/VRP_Arming.h"
#include "libraries/VRP_AHRS/VRP_AHRS.h"
#include "libraries/VRP_BattMonitor/VRP_BattMonitor.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_GCS_MAVLink/VRP_GCS_MAVLink.h"
#include "libraries/VRP_InertialSensor/VRP_InertialSensor.h"
#include "libraries/VRP_Logger/VRP_Logger.h"
#include "libraries/VRP_Mission/VRP_Mission.h"
#include "libraries/VRP_NavEKF3/VRP_NavEKF3.h"
#include "libraries/VRP_OpenDroneID/VRP_OpenDroneID.h"
#include "libraries/VRP_Rally/VRP_Rally.h"
#include "libraries/VRP_SmartRTL/VRP_SmartRTL.h"
#include "libraries/VRP_Terrain/VRP_Terrain.h"
#include "libraries/VRP_Stats/VRP_Stats.h"
#include "middleware/params/VRP_Param.h"
#include "middleware/uorb/UORB.h"
#include "modules/sensor_core/SensorCore.h"
#include "modules/simulation/FDM.h"

namespace vrp {

class SafetyCore {
public:
  bool init(const std::string &vehicle, VRPParamStore &params);
  void configure_adsb_test(double intruder_x_m);
  void configure_calcio_mission_test();
  void configure_calcio_home();
  void update(double dt_s, uint64_t time_ms, const FDMState &fdm, UORB &uorb);
  void apply_mavlink_action(const MavlinkRxAction &action);
  void note_gcs_link(uint64_t tick);

  bool is_armed() const;
  bool fence_breached() const;
  std::string flight_mode() const;
  const Attitude &attitude() const;
  const LocalPosition &position() const;
  const BatteryStatus &battery() const;
  const GpsSample &gps() const;
  std::string logger_summary() const;
  std::string sensors_summary() const;
  std::string failsafe_summary() const;
  std::string smart_rtl_summary() const;
  std::string avoidance_summary() const;
  const AvoidanceOutput &avoidance() const { return avoidance_out_; }
  std::string stats_summary() const;
  std::string open_drone_id_line() const;
  bool mission_active() const;
  bool mission_complete() const;
  size_t mission_index() const;
  size_t mission_waypoint_count() const;
  Waypoint mission_prev_target() const;
  bool mission_get_item_int(uint16_t seq, int32_t &lat_e7, int32_t &lon_e7, float &alt_m) const;
  bool mission_upload_ack_pending() const;
  void clear_mission_upload_ack();
  MissionTxView build_mission_tx(const MavlinkRxAction &rx) const;
  int consume_mission_item_reached();
  const RangeFinderSample &rangefinder() const;
  const ProximitySample &proximity() const;
  const AdsbVehicle &adsb() const;
  const AirspeedSample &airspeed() const;
  const OpticalFlowSample &optical_flow() const;
  const RallyStatus &rally_status() const { return rally_status_; }
  const SmartRtlState &smart_rtl_state() const { return smart_rtl_state_; }
  bool ekf_gps_glitch() const { return ekf3_.gps_glitch(); }
  TerrainSample terrain_sample() const { return terrain_sample_; }
  double baro_ground_correction() const { return baro_ground_corr_; }
  Waypoint mission_target() const;
  Waypoint nav_target() const;
  bool rtl_nav_active() const;
  const std::string &mission_status() const;

private:
  SensorGroundTruth truth_from_fdm(const FDMState &fdm) const;
  void enter_rtl(const std::string &reason);

  std::string vehicle_;
  uint64_t tick_{0};
  SensorCore sensors_{};
  VRP_InertialSensor ins_{};
  VRP_AHRS ahrs_{};
  VRP_NavEKF3 ekf3_{};
  VRP_BattMonitor batt_{};
  VRP_Arming arming_{};
  VRP_Mission mission_{};
  VRP_AC_Fence fence_{};
  VRP_Logger logger_{};
  VRP_SmartRTL smart_rtl_{};
  VRP_Rally rally_{};
  VRP_Terrain terrain_{};
  VRP_AdvancedFailsafe failsafe_{};
  VRP_AC_Avoidance avoidance_{};
  VRP_Stats stats_{};
  VRP_OpenDroneID open_drone_id_{};
  Attitude attitude_{};
  LocalPosition position_{};
  BatteryStatus battery_{};
  GpsSample gps_{};
  SmartRtlState smart_rtl_state_{};
  std::string mode_{"Init"};
  bool fence_breach_{false};
  bool rtl_active_{false};
  uint16_t mission_upload_expected_{0};
  bool mission_upload_ack_pending_{false};
  bool mission_rtl_disabled_{false};
  AvoidanceOutput avoidance_out_{};
  RallyStatus rally_status_{};
  TerrainSample terrain_sample_{};
  double baro_ground_corr_{0.0};
  std::string open_drone_line_{"OPEN_DRONE_ID idle"};
};

} // namespace vrp
