#include "modules/mavlink/MavlinkCodec.h"

#include <algorithm>
#include <cstring>

namespace vrp {

uint16_t MavlinkCodec::crc_accumulate(uint8_t data, uint16_t crc) {
  uint8_t tmp = data ^ static_cast<uint8_t>(crc & 0xFFU);
  tmp ^= static_cast<uint8_t>((tmp << 4U) & 0xFFU);
  return static_cast<uint16_t>((crc >> 8) ^ (static_cast<uint16_t>(tmp) << 8) ^ (static_cast<uint16_t>(tmp) << 3) ^
                               (static_cast<uint16_t>(tmp) >> 4));
}

uint16_t MavlinkCodec::crc_calculate(const uint8_t *data, size_t len, uint8_t crc_extra) {
  uint16_t crc = 0xFFFFU;
  for (size_t i = 0; i < len; ++i) {
    crc = crc_accumulate(data[i], crc);
  }
  crc = crc_accumulate(crc_extra, crc);
  return crc;
}

std::vector<uint8_t> MavlinkCodec::pack_v2(uint8_t sysid, uint8_t compid, uint32_t msgid, uint8_t crc_extra,
                                             const uint8_t *payload, uint8_t payload_len, uint8_t &seq) {
  uint8_t header[9];
  header[0] = payload_len;
  header[1] = 0;
  header[2] = 0;
  header[3] = seq++;
  header[4] = sysid;
  header[5] = compid;
  header[6] = static_cast<uint8_t>(msgid & 0xFFU);
  header[7] = static_cast<uint8_t>((msgid >> 8) & 0xFFU);
  header[8] = static_cast<uint8_t>((msgid >> 16) & 0xFFU);

  std::vector<uint8_t> crc_input;
  crc_input.insert(crc_input.end(), header, header + 9);
  crc_input.insert(crc_input.end(), payload, payload + payload_len);
  const uint16_t crc = crc_calculate(crc_input.data(), crc_input.size(), crc_extra);

  std::vector<uint8_t> frame;
  frame.reserve(12 + payload_len);
  frame.push_back(0xFD);
  frame.insert(frame.end(), header, header + 9);
  frame.insert(frame.end(), payload, payload + payload_len);
  frame.push_back(static_cast<uint8_t>(crc & 0xFFU));
  frame.push_back(static_cast<uint8_t>((crc >> 8) & 0xFFU));
  return frame;
}

std::vector<uint8_t> MavlinkCodec::heartbeat(uint8_t sysid, uint8_t compid, uint8_t base_mode, uint8_t system_status,
                                             uint8_t &seq) {
  uint8_t payload[9]{};
  std::memset(payload, 0, sizeof(payload));
  payload[4] = base_mode;
  payload[5] = system_status;
  payload[8] = 3;
  return pack_v2(sysid, compid, 0, 50, payload, 9, seq);
}

std::vector<uint8_t> MavlinkCodec::attitude(uint8_t sysid, uint8_t compid, float roll, float pitch, float yaw,
                                            float rollspeed, float pitchspeed, float yawspeed, uint8_t &seq) {
  uint8_t payload[28]{};
  std::memcpy(payload + 0, &roll, 4);
  std::memcpy(payload + 4, &pitch, 4);
  std::memcpy(payload + 8, &yaw, 4);
  std::memcpy(payload + 12, &rollspeed, 4);
  std::memcpy(payload + 16, &pitchspeed, 4);
  std::memcpy(payload + 20, &yawspeed, 4);
  return pack_v2(sysid, compid, 30, 39, payload, 28, seq);
}

std::vector<uint8_t> MavlinkCodec::sys_status(uint8_t sysid, uint8_t compid, uint16_t voltage_mv, uint8_t battery_pct,
                                              uint8_t &seq) {
  uint8_t payload[31]{};
  std::memset(payload, 0, sizeof(payload));
  std::memcpy(payload + 0, &voltage_mv, 2);
  payload[30] = battery_pct;
  return pack_v2(sysid, compid, 1, 124, payload, 31, seq);
}

uint8_t MavlinkCodec::crc_extra_for(uint32_t msgid) {
  switch (msgid) {
  case 0:
    return 50;
  case 1:
    return 124;
  case 24:
    return 24;
  case 30:
    return 39;
  case 33:
    return 104;
  case 44:
    return 221;
  case 46:
    return 11;
  case 132:
    return 85;
  case 43:
    return 132;
  case 51:
    return 196;
  case 73:
    return 38;
  case 11:
    return 89;
  case 42:
    return 28;
  case 47:
    return 153;
  case 76:
    return 152;
  case 20:
    return 214;
  case 22:
    return 220;
  case 23:
    return 168;
  case 242:
    return 104;
  default:
    return 0;
  }
}

std::vector<uint8_t> MavlinkCodec::global_position_int(uint8_t sysid, uint8_t compid, int32_t lat_e7, int32_t lon_e7,
                                                       int32_t alt_mm, uint8_t &seq) {
  uint8_t payload[28]{};
  std::memset(payload, 0, sizeof(payload));
  std::memcpy(payload + 0, &lat_e7, 4);
  std::memcpy(payload + 4, &lon_e7, 4);
  std::memcpy(payload + 8, &alt_mm, 4);
  return pack_v2(sysid, compid, 33, 104, payload, 28, seq);
}

std::vector<uint8_t> MavlinkCodec::gps_raw_int(uint8_t sysid, uint8_t compid, int32_t lat_e7, int32_t lon_e7,
                                               int32_t alt_mm, uint8_t fix_type, uint8_t &seq) {
  uint8_t payload[30]{};
  std::memset(payload, 0, sizeof(payload));
  std::memcpy(payload + 0, &lat_e7, 4);
  std::memcpy(payload + 4, &lon_e7, 4);
  std::memcpy(payload + 8, &alt_mm, 4);
  payload[24] = fix_type;
  payload[29] = fix_type;
  return pack_v2(sysid, compid, 24, 24, payload, 30, seq);
}

std::vector<uint8_t> MavlinkCodec::set_mode(uint8_t sysid, uint8_t compid, uint8_t base_mode, uint32_t custom_mode,
                                            uint8_t &seq) {
  uint8_t payload[7]{};
  payload[0] = sysid;
  payload[1] = 1;
  payload[2] = base_mode;
  std::memcpy(payload + 3, &custom_mode, 4);
  return pack_v2(sysid, compid, 11, 89, payload, 7, seq);
}

std::vector<uint8_t> MavlinkCodec::mission_current(uint8_t sysid, uint8_t compid, uint16_t mission_seq, uint8_t &seq) {
  uint8_t payload[2]{};
  std::memcpy(payload, &mission_seq, 2);
  return pack_v2(sysid, compid, 42, 28, payload, 2, seq);
}

std::vector<uint8_t> MavlinkCodec::mission_ack(uint8_t sysid, uint8_t compid, uint8_t mission_type, uint8_t result,
                                               uint8_t &seq) {
  uint8_t payload[3]{};
  payload[0] = sysid;
  payload[1] = mission_type;
  payload[2] = result;
  return pack_v2(sysid, compid, 47, 153, payload, 3, seq);
}

std::vector<uint8_t> MavlinkCodec::mission_count(uint8_t sysid, uint8_t compid, uint16_t count, uint8_t mission_type,
                                                 uint8_t &seq) {
  uint8_t payload[4]{};
  payload[0] = sysid;
  payload[1] = mission_type;
  std::memcpy(payload + 2, &count, 2);
  return pack_v2(sysid, compid, 44, 221, payload, 4, seq);
}

std::vector<uint8_t> MavlinkCodec::mission_item_int(uint8_t sysid, uint8_t compid, uint16_t item_seq, uint8_t frame,
                                                    int32_t lat_e7, int32_t lon_e7, float alt_m, uint8_t &seq_out) {
  uint8_t payload[37]{};
  std::memset(payload, 0, sizeof(payload));
  std::memcpy(payload + 0, &item_seq, 2);
  payload[2] = frame;
  payload[3] = 0; // command MAV_CMD_NAV_WAYPOINT
  payload[4] = sysid;
  payload[5] = 1;
  payload[6] = 0; // current
  payload[7] = 1; // autocontinue
  std::memcpy(payload + 24, &lat_e7, 4);
  std::memcpy(payload + 28, &lon_e7, 4);
  std::memcpy(payload + 32, &alt_m, 4);
  return pack_v2(sysid, compid, 73, 38, payload, 37, seq_out);
}

std::vector<uint8_t> MavlinkCodec::mission_item_reached(uint8_t sysid, uint8_t compid, uint16_t item_seq,
                                                        uint8_t &seq) {
  uint8_t payload[2]{};
  std::memcpy(payload, &item_seq, 2);
  return pack_v2(sysid, compid, 46, 11, payload, 2, seq);
}

std::vector<uint8_t> MavlinkCodec::distance_sensor(uint8_t sysid, uint8_t compid, float distance_m, uint8_t &seq) {
  uint8_t payload[14]{};
  std::memset(payload, 0, sizeof(payload));
  std::memcpy(payload + 8, &distance_m, 4);
  payload[12] = 0; // MAV_DISTANCE_SENSOR_LASER
  return pack_v2(sysid, compid, 132, 85, payload, 14, seq);
}

std::vector<uint8_t> MavlinkCodec::mission_request_list(uint8_t sysid, uint8_t compid, uint8_t &seq) {
  uint8_t payload[2]{sysid, compid};
  return pack_v2(sysid, compid, 43, 132, payload, 2, seq);
}

std::vector<uint8_t> MavlinkCodec::mission_request_int(uint8_t sysid, uint8_t compid, uint16_t mission_seq,
                                                       uint8_t &seq) {
  uint8_t payload[4]{sysid, compid, 0, 0};
  std::memcpy(payload + 2, &mission_seq, 2);
  return pack_v2(sysid, compid, 51, 196, payload, 4, seq);
}

std::vector<uint8_t> MavlinkCodec::command_long(uint8_t sysid, uint8_t compid, uint16_t command, float param1,
                                                uint8_t &seq) {
  uint8_t payload[33]{};
  std::memcpy(payload + 0, &param1, 4);
  std::memcpy(payload + 28, &command, 2);
  payload[30] = sysid;
  payload[31] = 1;
  return pack_v2(sysid, compid, 76, 152, payload, 33, seq);
}

std::vector<uint8_t> MavlinkCodec::param_request_read(uint8_t sysid, uint8_t compid, uint16_t param_index,
                                                      const char *param_id, uint8_t &seq) {
  uint8_t payload[20]{};
  std::memcpy(payload + 0, &param_index, 2);
  payload[2] = sysid;
  payload[3] = compid;
  std::memset(payload + 4, 0, 16);
  if (param_id != nullptr) {
    std::memcpy(payload + 4, param_id, std::min<std::size_t>(16, std::strlen(param_id)));
  }
  return pack_v2(sysid, compid, 20, 214, payload, 20, seq);
}

std::vector<uint8_t> MavlinkCodec::param_value(uint8_t sysid, uint8_t compid, const char *param_id, float value,
                                               uint16_t param_index, uint16_t param_count, uint8_t &seq) {
  uint8_t payload[25]{};
  std::memcpy(payload + 0, &value, 4);
  std::memcpy(payload + 4, &param_count, 2);
  std::memcpy(payload + 6, &param_index, 2);
  std::memset(payload + 8, 0, 16);
  if (param_id != nullptr) {
    std::memcpy(payload + 8, param_id, std::min<std::size_t>(16, std::strlen(param_id)));
  }
  return pack_v2(sysid, compid, 22, 220, payload, 25, seq);
}

std::vector<uint8_t> MavlinkCodec::param_set(uint8_t sysid, uint8_t compid, const char *param_id, float value,
                                             uint8_t &seq) {
  uint8_t payload[23]{};
  std::memcpy(payload + 0, &value, 4);
  payload[4] = sysid;
  payload[5] = compid;
  std::memset(payload + 6, 0, 16);
  if (param_id != nullptr) {
    std::memcpy(payload + 6, param_id, std::min<std::size_t>(16, std::strlen(param_id)));
  }
  return pack_v2(sysid, compid, 23, 168, payload, 23, seq);
}

std::vector<uint8_t> MavlinkCodec::home_position(uint8_t sysid, uint8_t compid, int32_t lat_e7, int32_t lon_e7,
                                                int32_t alt_mm, uint8_t &seq) {
  uint8_t payload[52]{};
  std::memcpy(payload + 0, &lat_e7, 4);
  std::memcpy(payload + 4, &lon_e7, 4);
  std::memcpy(payload + 8, &alt_mm, 4);
  return pack_v2(sysid, compid, 242, 104, payload, 52, seq);
}

} // namespace vrp
