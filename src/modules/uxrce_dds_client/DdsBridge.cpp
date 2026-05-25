#include "modules/uxrce_dds_client/DdsBridge.h"

#include <sstream>

namespace vrp {

bool DdsBridge::init() {
  seq_ = 0;
  return true;
}

std::string DdsBridge::publish_status(const std::string &mode, bool armed, UORB &uorb) {
  const std::string payload = "mode=" + mode + " armed=" + (armed ? "1" : "0");
  uorb.publish("/vrp/out/vehicle_status", payload);
  return "DDS /vrp/out/vehicle_status " + payload;
}

std::string DdsBridge::publish_attitude(UORB &uorb) {
  const auto att = uorb.subscribe("vehicle/attitude");
  const std::string payload = att.value_or("att=idle");
  uorb.publish("/vrp/out/vehicle_attitude", payload);
  return "DDS /vrp/out/vehicle_attitude " + payload;
}

std::string DdsBridge::publish_position(UORB &uorb) {
  const auto pos = uorb.subscribe("estimator/local_position");
  const std::string payload = pos.value_or("pos=idle");
  uorb.publish("/vrp/out/vehicle_local_position", payload);
  return "DDS /vrp/out/vehicle_local_position " + payload;
}

std::string DdsBridge::publish_sensor_combined(UORB &uorb) {
  const auto gps = uorb.subscribe("sensor/gps");
  const auto baro = uorb.subscribe("sensor/baro");
  const auto imu = uorb.subscribe("sensor/imu");
  const std::string payload =
      "gps=" + gps.value_or("idle") + " baro=" + baro.value_or("idle") + " imu=" + imu.value_or("idle");
  uorb.publish("/vrp/out/sensor_combined", payload);
  return "DDS /vrp/out/sensor_combined " + payload;
}

std::string DdsBridge::poll_subscriptions(UORB &uorb) {
  const auto cmd = uorb.subscribe("/vrp/in/vehicle_command");
  if (cmd.has_value()) {
    uorb.publish("offboard/command", *cmd);
    return "DDS /vrp/in/vehicle_command " + *cmd;
  }
  return "DDS /vrp/in/vehicle_command idle";
}

std::string DdsBridge::tick(uint64_t time_ms, const std::string &mode, bool armed, UORB &uorb) {
  ++seq_;
  std::ostringstream oss;
  oss << publish_status(mode, armed, uorb) << " | " << publish_attitude(uorb) << " | " << publish_position(uorb)
      << " | " << publish_sensor_combined(uorb) << " | " << poll_subscriptions(uorb) << " seq=" << seq_
      << " t_ms=" << time_ms;
  return oss.str();
}

} // namespace vrp
