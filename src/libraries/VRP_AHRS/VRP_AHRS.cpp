#include "libraries/VRP_AHRS/VRP_AHRS.h"

#include <cmath>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AHRS::init() {
  attitude_ = Attitude{};
  initialized_ = false;
  return true;
}

Attitude VRP_AHRS::update(const ImuSample &imu, double dt_s) {
  const double roll_meas = std::atan2(imu.ay, imu.az);
  const double pitch_meas = std::atan2(-imu.ax, std::sqrt(VRP_Math::sq(imu.ay) + VRP_Math::sq(imu.az)));

  if (!initialized_) {
    attitude_.roll_rad = roll_meas;
    attitude_.pitch_rad = pitch_meas;
    attitude_.yaw_rad = 0.0;
    initialized_ = true;
    return attitude_;
  }

  constexpr double kGyroWeight = 0.98;
  attitude_.roll_rad = kGyroWeight * (attitude_.roll_rad + imu.gx * dt_s) + (1.0 - kGyroWeight) * roll_meas;
  attitude_.pitch_rad = kGyroWeight * (attitude_.pitch_rad + imu.gy * dt_s) + (1.0 - kGyroWeight) * pitch_meas;
  attitude_.yaw_rad = VRP_Math::wrap_pi(attitude_.yaw_rad + imu.gz * dt_s);
  return attitude_;
}

} // namespace vrp
