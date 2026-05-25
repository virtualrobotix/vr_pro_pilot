#pragma once

#include <string>

#include "libraries/VRP_AC_AttitudeControl/VRP_AC_AttitudeControl.h"
#include "libraries/VRP_APM_Control/VRP_APM_Control.h"
#include "libraries/VRP_AR_AttitudeControl/VRP_AR_AttitudeControl.h"
#include "libraries/VRP_AR_Motors/VRP_AR_Motors.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_Motors/VRP_Motors.h"
#include "libraries/VRP_Sailboat/VRP_Sailboat.h"
#include "libraries/VRP_TECS/VRP_TECS.h"
#include "libraries/VRP_WindVane/VRP_WindVane.h"
#include "middleware/params/VRP_Param.h"
#include "middleware/uorb/UORB.h"

namespace vrp {

class ControlCore {
public:
  bool init(const std::string &vehicle, VRPParamStore &params);
  MotorOutputQuad update_quad(bool armed, bool fence_breach, const Attitude &attitude, const LocalPosition &pos,
                              const VehicleSetpoints &sp, double dt_s, UORB &uorb);
  MotorOutputQuad update_vtol(bool armed, bool fence_breach, const Attitude &attitude, const LocalPosition &pos,
                              const VehicleSetpoints &sp, double airspeed_m_s, double dt_s, UORB &uorb);
  BoatActuators update_boat(bool armed, bool fence_breach, const Attitude &attitude, const LocalPosition &pos,
                            const VehicleSetpoints &sp, double dt_s, UORB &uorb);
  BoatActuators update_sailboat(bool armed, bool fence_breach, const Attitude &attitude, const LocalPosition &pos,
                                const VehicleSetpoints &sp, const WindSample &wind, double dt_s, UORB &uorb);
  BoatActuators update_subsea(bool armed, bool fence_breach, const VehicleSetpoints &sp, UORB &uorb);

  const MotorOutputQuad &last_quad() const { return quad_out_; }
  const BoatActuators &last_boat() const { return boat_out_; }
  const ArMotorsState &last_ar_motors() const { return last_ar_motors_; }

private:
  std::string vehicle_;
  double target_z_{-5.0};
  VRP_AC_AttitudeControl att_ctrl_{};
  VRP_APM_Control apm_ctrl_{};
  VRP_AR_AttitudeControl ar_att_ctrl_{};
  VRP_AR_Motors ar_motors_{};
  VRP_Sailboat sailboat_{};
  VRP_WindVane wind_vane_{};
  VRP_Motors motors_{};
  VRP_TECS tecs_{};
  MotorOutputQuad quad_out_{};
  BoatActuators boat_out_{};
  ArMotorsState last_ar_motors_{};
};

} // namespace vrp
