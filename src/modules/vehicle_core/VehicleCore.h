#pragma once

#include <string>

#include "libraries/VRP_OpticalFlow/VRP_OpticalFlow.h"
#include "libraries/VRP_Rally/VRP_Rally.h"
#include "libraries/VRP_SmartRTL/VRP_SmartRTL.h"
#include "libraries/VRP_Landing/VRP_Landing.h"
#include "libraries/VRP_LandingGear/VRP_LandingGear.h"
#include "libraries/VRP_OSD/VRP_OSD.h"
#include "libraries/VRP_RCProtocol/VRP_RCProtocol.h"
#include "libraries/VRP_RC_Channel/VRP_RC_Channel.h"
#include "libraries/VRP_RSSI/VRP_RSSI.h"
#include "libraries/VRP_Scripting/VRP_Scripting.h"
#include "libraries/VRP_GCS_MAVLink/VRP_GCS_MAVLink.h"
#include "middleware/params/VRP_Param.h"
#include "middleware/uorb/UORB.h"
#include "modules/copter_core/CopterCore.h"
#include "modules/mavlink/MavlinkMode.h"

namespace vrp {

class VehicleCore {
public:
  bool init(const std::string &vehicle, VRPParamStore &params);
  void update(uint64_t tick, bool armed, const std::string &safety_mode, const LocalPosition &pos,
              const BatteryStatus &battery, const WpNavOutput &nav, const RangeFinderSample &rng,
              const AvoidanceOutput &avoidance, const OpticalFlowSample &flow, const RallyStatus &rally,
              const SmartRtlState &smart_rtl, double terrain_amsl, bool terrain_valid, double baro_corr,
              bool gcs_link, UORB &uorb);
  void apply_mavlink(const MavlinkRxAction &action);

  const std::string &mode() const { return mode_; }
  const VehicleSetpoints &setpoints() const { return setpoints_; }
  const LandingSetpoint &landing() const { return landing_sp_; }
  const RcChannels &rc() const { return rc_; }
  std::string osd_line() const { return last_osd_; }
  std::string script_line() const { return script_line_; }
  std::string vtol_phase() const { return vtol_phase_; }
  std::string gear_line() const { return gear_.status(); }
  std::string rssi_line() const { return last_rssi_; }
  const CopterCore &copter() const { return copter_; }
  bool request_disarm() const { return vehicle_ == "quad" && copter_.request_disarm(); }
  const RssiSample &rssi() const { return last_rssi_sample_; }

private:
  void update_vtol_phase(uint64_t tick);
  void build_setpoints(const LocalPosition &pos, const WpNavOutput &nav, const RangeFinderSample &rng,
                       const AvoidanceOutput &avoidance, const OpticalFlowSample &flow, const RallyStatus &rally,
                       const SmartRtlState &smart_rtl, double terrain_amsl, bool terrain_valid, double baro_corr,
                       double dt_s);

  std::string vehicle_;
  std::string mode_{"Init"};
  std::string vtol_phase_{"MC"};
  std::string script_line_{"SCRIPT idle"};
  std::string last_osd_{};
  VehicleSetpoints setpoints_{};
  LandingSetpoint landing_sp_{};
  RcChannels rc_{};
  VRP_RCProtocol rc_proto_{};
  VRP_RC_Channel rc_map_{};
  VRP_OSD osd_{};
  VRP_Scripting scripting_{};
  VRP_Landing landing_{};
  VRP_LandingGear gear_{};
  VRP_RSSI rssi_{};
  CopterCore copter_{};
  RssiSample last_rssi_sample_{};
  std::string last_rssi_{"RSSI pct=0 valid=0"};
  double target_z_{-5.0};
  uint64_t tick_{0};
  bool mavlink_mode_active_{false};
  std::string mavlink_mode_{};
};

} // namespace vrp
