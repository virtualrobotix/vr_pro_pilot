#pragma once
/**
 * @module  modules/uxrce_dds_client/DdsBridge
 * @dal     C
 * @req     VRP-LLRD-AP_DDS
 * @parity  ArduPilot AP_DDS
 * @status  partial
 */

#include <string>

#include "middleware/uorb/UORB.h"

namespace vrp {

class DdsBridge {
public:
  bool init();
  std::string publish_status(const std::string &mode, bool armed, UORB &uorb);
  std::string publish_attitude(UORB &uorb);
  std::string publish_position(UORB &uorb);
  std::string publish_sensor_combined(UORB &uorb);
  std::string poll_subscriptions(UORB &uorb);
  std::string tick(uint64_t time_ms, const std::string &mode, bool armed, UORB &uorb);

private:
  uint32_t seq_{0};
};

} // namespace vrp
