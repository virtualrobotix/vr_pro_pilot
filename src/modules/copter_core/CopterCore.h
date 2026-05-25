#pragma once

#include <string>

#include "libraries/VRP_AC_AutoTune/VRP_AC_AutoTune.h"
#include "libraries/VRP_AC_Avoidance/VRP_AC_Avoidance.h"
#include "libraries/VRP_AC_CustomControl/VRP_AC_CustomControl.h"
#include "libraries/VRP_AC_InputManager/VRP_AC_InputManager.h"
#include "libraries/VRP_AC_PID/VRP_AC_PID.h"
#include "libraries/VRP_AC_PrecLand/VRP_AC_PrecLand.h"
#include "libraries/VRP_AC_Sprayer/VRP_AC_Sprayer.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_Follow/VRP_Follow.h"
#include "libraries/VRP_InertialNav/VRP_InertialNav.h"
#include "libraries/VRP_Landing/VRP_Landing.h"
#include "libraries/VRP_OpticalFlow/VRP_OpticalFlow.h"
#include "libraries/VRP_Rally/VRP_Rally.h"
#include "libraries/VRP_SmartRTL/VRP_SmartRTL.h"
#include "libraries/VRP_SurfaceDistance/VRP_SurfaceDistance.h"
#include "libraries/VRP_Takeoff/VRP_Takeoff.h"
#include "libraries/VRP_Terrain/VRP_Terrain.h"
#include "middleware/params/VRP_Param.h"

namespace vrp {

struct CopterAuxInputs {
  const OpticalFlowSample *flow{nullptr};
  const RallyStatus *rally{nullptr};
  const SmartRtlState *smart_rtl{nullptr};
  double follow_target_x{100.0};
  double follow_target_y{0.0};
  bool follow_enabled{false};
  double terrain_amsl_m{0.0};
  bool terrain_valid{false};
  double baro_ground_corr{0.0};
  bool flow_fusion{false};
};

class CopterCore {
public:
  bool init(VRPParamStore &params);
  VehicleSetpoints build_setpoints(const std::string &mode, const LocalPosition &pos, const WpNavOutput &nav,
                                   const RcChannels &rc, const AvoidanceOutput &avoidance,
                                   const RangeFinderSample &rng, LandingSetpoint &landing_sp, double target_z,
                                   double dt_s, const CopterAuxInputs &aux = {});
  const PrecLandState &prec_land() const { return prec_land_; }
  const AutoTuneState &autotune() const { return autotune_state_; }
  const SprayerState &sprayer() const { return sprayer_state_; }
  const CustomControlState &custom_control() const { return custom_state_; }
  const AcPidState &ac_pid() const { return ac_pid_state_; }
  const InertialNavState &inertial_nav() const { return inertial_state_; }
  const SurfaceDistanceSample &surface() const { return surface_state_; }
  const FollowState &follow() const { return follow_state_; }
  const TakeoffState &takeoff() const { return takeoff_state_; }
  float autotune_scale() const;
  float motor_spool() const { return motor_spool_; }
  bool request_disarm() const { return request_disarm_; }

private:
  void apply_nav_attitude(VehicleSetpoints &sp, const WpNavOutput &nav, double max_tilt_rad, double target_z,
                          const LocalPosition &pos, const CopterAuxInputs &aux) const;
  void apply_avoidance(VehicleSetpoints &sp, const AvoidanceOutput &avoidance, double max_tilt_rad) const;
  void apply_rc_stabilize(VehicleSetpoints &sp, const RcChannels &rc, double max_tilt_rad) const;
  void apply_flow_loiter(VehicleSetpoints &sp, const OpticalFlowSample &flow, double max_tilt_rad) const;
  void apply_custom_overlay(VehicleSetpoints &sp, const CustomControlState &custom, double max_tilt_rad) const;
  double terrain_target_z(double target_z, const CopterAuxInputs &aux) const;

  VRP_AC_InputManager input_mgr_{};
  VRP_AC_PrecLand precland_{};
  VRP_AC_AutoTune autotune_lib_{};
  VRP_AC_CustomControl custom_ctl_{};
  VRP_AC_Sprayer sprayer_{};
  VRP_AC_PID ac_pid_{};
  VRP_Landing landing_{};
  VRP_InertialNav inertial_nav_{};
  VRP_SurfaceDistance surface_{};
  VRP_Follow follow_{};
  VRP_Rally rally_{};
  VRP_Takeoff takeoff_{};
  VRP_Terrain terrain_{};
  PrecLandState prec_land_{};
  AutoTuneState autotune_state_{};
  SprayerState sprayer_state_{};
  CustomControlState custom_state_{};
  AcPidState ac_pid_state_{};
  InertialNavState inertial_state_{};
  SurfaceDistanceSample surface_state_{};
  FollowState follow_state_{};
  TakeoffState takeoff_state_{};
  double max_tilt_rad_{0.61};
  double loiter_radius_m_{5.0};
  float motor_spool_{0.0F};
  bool request_disarm_{false};
};

} // namespace vrp
