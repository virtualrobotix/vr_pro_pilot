#pragma once
/**
 * @module  libraries/VRP_GCS_MAVLink
 * @dal     C
 * @req     VRP-LLRD-GCS_MAVLink
 * @parity  ArduPilot GCS_MAVLink
 * @status  partial
 */
/**
 * @module  libraries/VRP_GCS_MAVLink
 * @dal     C
 * @req     VRP-LLRD-GCS_MAVLink
 */
#include <cstdint>
#include <string>
#include <vector>

#include "libraries/VRP_Common/VRP_Common.h"
#include "modules/mavlink/MavlinkParser.h"

namespace vrp {

struct WindSample;

struct MavlinkRxAction {
  bool arm{false};
  bool disarm{false};
  bool set_mode{false};
  uint32_t custom_mode{0};
  bool mission_clear{false};
  bool mission_item{false};
  bool mission_request_list{false};
  bool mission_request_item{false};
  uint16_t mission_expected{0};
  uint16_t mission_request_seq{0};
  int32_t mission_lat_e7{0};
  int32_t mission_lon_e7{0};
  float mission_alt_m{0.0F};
  bool param_request{false};
  bool param_set{false};
  uint16_t param_index{0};
  char param_id[17]{};
  float param_value{0.0F};
};

struct MissionTxView {
  size_t waypoint_count{0};
  bool send_upload_ack{false};
  bool send_count{false};
  bool send_item{false};
  bool send_item_reached{false};
  bool send_distance_sensor{false};
  uint16_t item_seq{0};
  uint16_t reached_seq{0};
  float distance_m{0.0F};
  int32_t item_lat_e7{0};
  int32_t item_lon_e7{0};
  float item_alt_m{0.0F};
};

struct MavlinkTxBundle {
  MissionTxView mission{};
  bool send_param_value{false};
  char param_id[17]{};
  float param_value{0.0F};
  uint16_t param_index{0};
  uint16_t param_count{0};
  bool send_home_position{false};
  int32_t home_lat_e7{450000000};
  int32_t home_lon_e7{90000000};
  int32_t home_alt_mm{0};
};

class VRP_GCS_MAVLink {
public:
  bool init();
  void shutdown();
  std::string transmit(const std::string &vehicle, bool armed, const std::string &mode, const Attitude &attitude,
                       const LocalPosition &pos, const GpsSample &gps, const BatteryStatus &battery, uint64_t time_ms,
                       uint16_t mission_seq = 0xFFFF, const MavlinkTxBundle *tx = nullptr,
                       const WindSample *wind = nullptr);
  std::string last_mission_tx_summary() const { return last_mission_tx_; }
  std::string poll(MavlinkRxAction &action);
  bool inject_frame_for_test(const std::vector<uint8_t> &frame, MavlinkRxAction &action);

private:
  bool dispatch_message(const MavlinkMessage &msg, MavlinkRxAction &action);

  uint8_t seq_{0};
  bool ready_{false};
  std::string last_mission_tx_{"MISSION_TX idle"};
};

} // namespace vrp
