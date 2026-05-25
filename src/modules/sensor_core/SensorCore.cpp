#include "modules/sensor_core/SensorCore.h"

#include <cmath>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool SensorCore::init() {
  gps_.init(45.0, 9.0);
  baro_.init();
  compass_.init();
  rangefinder_.init(0.0, 30.0);
  proximity_.init(3.0, 25.0);
  adsb_.init();
  airspeed_.init();
  optical_flow_.init();
  have_prev_ = false;
  last_ = SensorSnapshot{};
  return true;
}

SensorSnapshot SensorCore::update(const FDMState &fdm, uint64_t time_us, uint64_t tick) {
  double speed = 0.0;
  double vx = 0.0;
  double vy = 0.0;
  if (have_prev_) {
    const double dx = fdm.x - prev_x_;
    const double dy = fdm.y - prev_y_;
    vx = dx / 0.02;
    vy = dy / 0.02;
    speed = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy)) / 0.02;
  }
  prev_x_ = fdm.x;
  prev_y_ = fdm.y;
  have_prev_ = true;

  GpsInput in{};
  in.x_m = fdm.x;
  in.y_m = fdm.y;
  in.z_m = fdm.z;
  in.speed_m_s = speed;

  last_.gps = gps_.update(in, time_us);
  last_.baro = baro_.update(-fdm.z, time_us);
  last_.compass = compass_.update(fdm.yaw_deg, time_us);
  last_.rangefinder = rangefinder_.update(fdm.z, time_us);
  last_.adsb = adsb_.update(tick, fdm.x, fdm.y, -fdm.z);
  last_.airspeed = airspeed_.update(speed, time_us);
  last_.optical_flow = optical_flow_.update(vx, vy, std::max(0.05, -fdm.z), time_us);
  last_.proximity = proximity_.update(fdm.x, fdm.y, last_.rangefinder, &last_.adsb);

  last_.measurement.x = fdm.x;
  last_.measurement.y = fdm.y;
  last_.measurement.z = -last_.baro.alt_m;
  last_.measurement.valid = last_.gps.valid && last_.baro.valid;
  return last_;
}

} // namespace vrp
