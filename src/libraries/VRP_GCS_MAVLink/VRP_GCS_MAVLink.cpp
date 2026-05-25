#include "libraries/VRP_GCS_MAVLink/VRP_GCS_MAVLink.h"

#include <cmath>
#include <cstring>
#include <sstream>

#include "libraries/VRP_WindVane/VRP_WindVane.h"
#include "libraries/VRP_Math/VRP_Math.h"
#include "modules/mavlink/MavlinkCodec.h"
#include "modules/mavlink/MavlinkMode.h"
#include "modules/mavlink/MavlinkParser.h"
#include "modules/mavlink/MavlinkUdp.h"

namespace vrp {

namespace {
MavlinkUdp g_udp;
MavlinkParser g_parser;
} // namespace

bool VRP_GCS_MAVLink::init() {
  ready_ = g_udp.init("127.0.0.1", 14550);
  seq_ = 0;
  return ready_;
}

void VRP_GCS_MAVLink::shutdown() {
  g_udp.close_socket();
}

std::string VRP_GCS_MAVLink::transmit(const std::string &vehicle, bool armed, const std::string &mode,
                                      const Attitude &attitude, const LocalPosition &pos, const GpsSample &gps,
                                      const BatteryStatus &battery, uint64_t time_ms, uint16_t mission_seq,
                                      const MavlinkTxBundle *tx, const WindSample *wind) {
  if (!ready_) {
    return "MAVLINK_V2 skipped";
  }

  const uint32_t custom_mode = mavlink_custom_mode_from_mode(vehicle, mode);
  uint8_t base_mode = 0x01U | 0x10U | 0x40U;
  if (armed) {
    base_mode |= 0x80U;
  }
  const auto hb = MavlinkCodec::heartbeat(1, 1, mavlink_type_for_vehicle(vehicle), 3U, base_mode, armed ? 4U : 3U,
                                          custom_mode, seq_);
  const auto att =
      MavlinkCodec::attitude(1, 1, static_cast<float>(attitude.roll_rad), static_cast<float>(attitude.pitch_rad),
                             static_cast<float>(attitude.yaw_rad), 0.0F, 0.0F, 0.0F, seq_);
  const uint16_t voltage_mv = static_cast<uint16_t>(battery.voltage_v * 1000.0);
  const auto stat = MavlinkCodec::sys_status(1, 1, voltage_mv, static_cast<uint8_t>(battery.remaining_pct), seq_);
  const int32_t lat_e7 = static_cast<int32_t>(gps.lat_deg * 1e7);
  const int32_t lon_e7 = static_cast<int32_t>(gps.lon_deg * 1e7);
  const int32_t alt_mm = static_cast<int32_t>(gps.alt_m * 1000.0);
  const int32_t rel_alt_mm = alt_mm;
  const int16_t vx_cm_s = static_cast<int16_t>(pos.vx * 100.0);
  const int16_t vy_cm_s = static_cast<int16_t>(pos.vy * 100.0);
  const int16_t vz_cm_s = static_cast<int16_t>(pos.vz * 100.0);
  uint16_t hdg_cdeg = 65535U;
  double yaw_rad = attitude.yaw_rad;
  while (yaw_rad < 0.0) {
    yaw_rad += 6.283185307179586;
  }
  while (yaw_rad >= 6.283185307179586) {
    yaw_rad -= 6.283185307179586;
  }
  hdg_cdeg = static_cast<uint16_t>(yaw_rad / 6.283185307179586 * 36000.0);
  const auto gpi = MavlinkCodec::global_position_int(1, 1, static_cast<uint32_t>(time_ms), lat_e7, lon_e7, alt_mm,
                                                     rel_alt_mm, vx_cm_s, vy_cm_s, vz_cm_s, hdg_cdeg, seq_);
  const auto gps_raw = MavlinkCodec::gps_raw_int(1, 1, lat_e7, lon_e7, alt_mm, gps.fix_type, seq_);
  const float groundspeed = static_cast<float>(std::hypot(pos.vx, pos.vy));
  const int16_t heading_deg = static_cast<int16_t>(hdg_cdeg / 100);
  const uint16_t throttle_pct =
      static_cast<uint16_t>(VRP_Math::clamp(static_cast<double>(groundspeed) * 20.0, 0.0, 100.0));
  const auto hud = MavlinkCodec::vfr_hud(1, 1, groundspeed, groundspeed, heading_deg, throttle_pct,
                                         static_cast<float>(gps.alt_m), static_cast<float>(pos.vz), seq_);

  std::vector<std::vector<uint8_t>> frames = {hb, att, stat, gpi, gps_raw, hud};
  if (mission_seq != 0xFFFF) {
    frames.push_back(MavlinkCodec::mission_current(1, 1, mission_seq, seq_));
  }

  std::ostringstream mission_oss;
  mission_oss << "MISSION_TX";
  const MissionTxView *mission_tx = tx != nullptr ? &tx->mission : nullptr;
  if (mission_tx != nullptr) {
    if (mission_tx->send_upload_ack) {
      frames.push_back(MavlinkCodec::mission_ack(1, 1, 0, 0, seq_));
      mission_oss << " ack=0";
    }
    if (mission_tx->send_count) {
      frames.push_back(MavlinkCodec::mission_count(1, 1, static_cast<uint16_t>(mission_tx->waypoint_count), 0, seq_));
      mission_oss << " count=" << mission_tx->waypoint_count;
    }
    if (mission_tx->send_item) {
      frames.push_back(MavlinkCodec::mission_item_int(1, 1, mission_tx->item_seq, 3, mission_tx->item_lat_e7,
                                                      mission_tx->item_lon_e7, mission_tx->item_alt_m, seq_));
      mission_oss << " item=" << mission_tx->item_seq;
    }
    if (mission_tx->send_item_reached) {
      frames.push_back(MavlinkCodec::mission_item_reached(1, 1, mission_tx->reached_seq, seq_));
      mission_oss << " reached=" << mission_tx->reached_seq;
    }
    if (mission_tx->send_distance_sensor) {
      frames.push_back(MavlinkCodec::distance_sensor(1, 1, mission_tx->distance_m, seq_));
      mission_oss << " rng=" << mission_tx->distance_m;
    }
  }
  if (tx != nullptr) {
    if (tx->send_param_value) {
      frames.push_back(MavlinkCodec::param_value(1, 1, tx->param_id, tx->param_value, tx->param_index, tx->param_count,
                                                 seq_));
      mission_oss << " param=" << tx->param_id;
    }
    if (tx->send_home_position) {
      frames.push_back(MavlinkCodec::home_position(1, 1, tx->home_lat_e7, tx->home_lon_e7, tx->home_alt_mm, seq_));
      mission_oss << " home=1";
    }
  }
  if (wind != nullptr && wind->valid) {
    const float dir_deg =
        static_cast<float>(std::fmod(wind->direction_rad / 6.283185307179586 * 360.0 + 360.0, 360.0));
    frames.push_back(MavlinkCodec::wind(1, 1, dir_deg, static_cast<float>(wind->speed_m_s), 0.0F, seq_));
  }
  if (mission_oss.str() == "MISSION_TX") {
    mission_oss << " idle";
  }
  last_mission_tx_ = mission_oss.str();

  size_t sent = 0;
  size_t bytes = 0;
  for (const auto &frame : frames) {
    bytes += frame.size();
    if (g_udp.send(frame)) {
      ++sent;
    }
  }

  std::ostringstream oss;
  oss << "MAVLINK_V2 sent=" << sent << " bytes=" << bytes << " t_ms=" << time_ms;
  if (mission_seq != 0xFFFF) {
    oss << " mission_seq=" << mission_seq;
  }
  return oss.str();
}

bool VRP_GCS_MAVLink::dispatch_message(const MavlinkMessage &msg, MavlinkRxAction &action) {
  if (msg.msgid == 76 && msg.payload.size() >= 33) {
    float param1 = 0.0F;
    uint16_t command = 0;
    std::memcpy(&param1, msg.payload.data(), 4);
    std::memcpy(&command, msg.payload.data() + 28, 2);
    if (command == 400) {
      if (param1 >= 0.5F) {
        action.arm = true;
      } else {
        action.disarm = true;
      }
      return true;
    }
    if (command == 176) {
      float param2 = 0.0F;
      std::memcpy(&param2, msg.payload.data() + 4, 4);
      if (param1 >= 0.5F) {
        action.set_mode = true;
        action.custom_mode = static_cast<uint32_t>(param2);
      }
      return true;
    }
  }
  if (msg.msgid == 11 && msg.payload.size() >= 7) {
    uint32_t custom = 0;
    std::memcpy(&custom, msg.payload.data() + 3, 4);
    action.set_mode = true;
    action.custom_mode = custom;
    return true;
  }
  if (msg.msgid == 43 && msg.payload.size() >= 2) {
    action.mission_request_list = true;
    return true;
  }
  if (msg.msgid == 51 && msg.payload.size() >= 4) {
    uint16_t req_seq = 0;
    std::memcpy(&req_seq, msg.payload.data() + 2, 2);
    action.mission_request_item = true;
    action.mission_request_seq = req_seq;
    return true;
  }
  if (msg.msgid == 44 && msg.payload.size() >= 2) {
    uint16_t count = 0;
    std::memcpy(&count, msg.payload.data(), 2);
    action.mission_clear = true;
    action.mission_expected = count;
    return true;
  }
  if (msg.msgid == 73 && msg.payload.size() >= 36) {
    int32_t lat_e7 = 0;
    int32_t lon_e7 = 0;
    float alt_m = 0.0F;
    std::memcpy(&lat_e7, msg.payload.data() + 24, 4);
    std::memcpy(&lon_e7, msg.payload.data() + 28, 4);
    std::memcpy(&alt_m, msg.payload.data() + 32, 4);
    action.mission_item = true;
    action.mission_lat_e7 = lat_e7;
    action.mission_lon_e7 = lon_e7;
    action.mission_alt_m = alt_m;
    return true;
  }
  if (msg.msgid == 20 && msg.payload.size() >= 20) {
    std::memcpy(&action.param_index, msg.payload.data(), 2);
    std::memcpy(action.param_id, msg.payload.data() + 4, 16);
    action.param_id[16] = '\0';
    action.param_request = true;
    return true;
  }
  if (msg.msgid == 23 && msg.payload.size() >= 23) {
    std::memcpy(&action.param_value, msg.payload.data(), 4);
    std::memcpy(action.param_id, msg.payload.data() + 6, 16);
    action.param_id[16] = '\0';
    action.param_set = true;
    return true;
  }
  return false;
}

std::string VRP_GCS_MAVLink::poll(MavlinkRxAction &action) {
  action = MavlinkRxAction{};
  std::vector<uint8_t> frame;
  if (!g_udp.recv_nonblock(frame)) {
    return "MAVLINK_RX idle";
  }
  MavlinkMessage msg;
  if (!g_parser.parse_v2(frame.data(), frame.size(), msg)) {
    return "MAVLINK_RX bad_crc";
  }
  dispatch_message(msg, action);
  std::ostringstream oss;
  oss << "MAVLINK_RX msg=" << msg.msgid;
  if (action.arm) {
    oss << " cmd=ARM";
  }
  if (action.disarm) {
    oss << " cmd=DISARM";
  }
  if (action.set_mode) {
    oss << " cmd=SET_MODE custom=" << action.custom_mode;
  }
  if (action.mission_item) {
    oss << " mission_item";
  }
  if (action.mission_request_list) {
    oss << " mission_req_list";
  }
  if (action.mission_request_item) {
    oss << " mission_req_item seq=" << action.mission_request_seq;
  }
  if (action.param_request) {
    oss << " param_req id=" << action.param_id;
  }
  if (action.param_set) {
    oss << " param_set id=" << action.param_id << " val=" << action.param_value;
  }
  return oss.str();
}

bool VRP_GCS_MAVLink::inject_frame_for_test(const std::vector<uint8_t> &frame, MavlinkRxAction &action) {
  action = MavlinkRxAction{};
  MavlinkMessage msg;
  if (!g_parser.parse_v2(frame.data(), frame.size(), msg)) {
    return false;
  }
  return dispatch_message(msg, action);
}

} // namespace vrp
