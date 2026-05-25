#include "libraries/VRP_Compass/VRP_Compass.h"

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Compass::init() {
  declination_deg_ = 0.0;
  return true;
}

CompassSample VRP_Compass::update(double yaw_deg, uint64_t time_us) {
  CompassSample out{};
  out.heading_deg = yaw_deg + declination_deg_;
  while (out.heading_deg >= 360.0) {
    out.heading_deg -= 360.0;
  }
  while (out.heading_deg < 0.0) {
    out.heading_deg += 360.0;
  }
  out.valid = true;
  out.time_us = time_us;
  (void)VRP_Math::deg_to_rad(yaw_deg);
  return out;
}

} // namespace vrp
