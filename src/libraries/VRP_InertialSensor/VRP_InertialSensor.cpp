#include "libraries/VRP_InertialSensor/VRP_InertialSensor.h"

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_InertialSensor::init() {
  have_prev_ = false;
  last_ = ImuSample{};
  return true;
}

ImuSample VRP_InertialSensor::update(const SensorGroundTruth &truth, uint64_t time_us, double dt_s) {
  ImuSample sample{};
  sample.ax = truth.ax;
  sample.ay = truth.ay;
  sample.az = truth.az;
  sample.gx = truth.gx;
  sample.gy = truth.gy;
  sample.gz = truth.gz;
  sample.time_us = time_us;

  if (!have_prev_) {
    prev_yaw_rad_ = VRP_Math::deg_to_rad(truth.yaw_deg);
    have_prev_ = true;
  } else if (dt_s > 0.0) {
    const double yaw_rad = VRP_Math::deg_to_rad(truth.yaw_deg);
    sample.gz = VRP_Math::wrap_pi(yaw_rad - prev_yaw_rad_) / dt_s;
    prev_yaw_rad_ = yaw_rad;
  }

  last_ = sample;
  return sample;
}

} // namespace vrp
