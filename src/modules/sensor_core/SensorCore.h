#pragma once

#include "libraries/VRP_ADSB/VRP_ADSB.h"
#include "libraries/VRP_Airspeed/VRP_Airspeed.h"
#include "libraries/VRP_Baro/VRP_Baro.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include "libraries/VRP_Compass/VRP_Compass.h"
#include "libraries/VRP_GPS/VRP_GPS.h"
#include "libraries/VRP_OpticalFlow/VRP_OpticalFlow.h"
#include "libraries/VRP_Proximity/VRP_Proximity.h"
#include "libraries/VRP_RangeFinder/VRP_RangeFinder.h"
#include "modules/simulation/FDM.h"

namespace vrp {

struct SensorSnapshot {
  GpsSample gps{};
  BaroSample baro{};
  CompassSample compass{};
  RangeFinderSample rangefinder{};
  ProximitySample proximity{};
  AdsbVehicle adsb{};
  AirspeedSample airspeed{};
  OpticalFlowSample optical_flow{};
  LocalPosition measurement{};
};

class SensorCore {
public:
  bool init();
  SensorSnapshot update(const FDMState &fdm, uint64_t time_us, uint64_t tick);

  const GpsSample &gps() const { return last_.gps; }
  const BaroSample &baro() const { return last_.baro; }
  const CompassSample &compass() const { return last_.compass; }
  const RangeFinderSample &rangefinder() const { return last_.rangefinder; }
  const ProximitySample &proximity() const { return last_.proximity; }
  const AdsbVehicle &adsb() const { return last_.adsb; }
  const AirspeedSample &airspeed() const { return last_.airspeed; }
  const OpticalFlowSample &optical_flow() const { return last_.optical_flow; }
  void set_adsb_intruder_x(double x_m) { adsb_.set_intruder_x(x_m); }

private:
  VRP_GPS gps_{};
  VRP_Baro baro_{};
  VRP_Compass compass_{};
  VRP_RangeFinder rangefinder_{};
  VRP_Proximity proximity_{};
  VRP_ADSB adsb_{};
  VRP_Airspeed airspeed_{};
  VRP_OpticalFlow optical_flow_{};
  SensorSnapshot last_{};
  double prev_x_{0.0};
  double prev_y_{0.0};
  bool have_prev_{false};
};

} // namespace vrp
