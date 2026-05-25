#pragma once

#include <cstdint>
#include <vector>

namespace vrp {

class MavlinkCodec {
public:
  static uint16_t crc_accumulate(uint8_t data, uint16_t crc);
  static uint16_t crc_calculate(const uint8_t *data, size_t len, uint8_t crc_extra);

  static std::vector<uint8_t> pack_v2(uint8_t sysid, uint8_t compid, uint32_t msgid, uint8_t crc_extra,
                                      const uint8_t *payload, uint8_t payload_len, uint8_t &seq);

  static std::vector<uint8_t> heartbeat(uint8_t sysid, uint8_t compid, uint8_t mav_type, uint8_t autopilot,
                                        uint8_t base_mode, uint8_t system_status, uint32_t custom_mode, uint8_t &seq);
  static std::vector<uint8_t> attitude(uint8_t sysid, uint8_t compid, float roll, float pitch, float yaw,
                                       float rollspeed, float pitchspeed, float yawspeed, uint8_t &seq);
  static std::vector<uint8_t> sys_status(uint8_t sysid, uint8_t compid, uint16_t voltage_mv, uint8_t battery_pct,
                                         uint8_t &seq);
  static std::vector<uint8_t> global_position_int(uint8_t sysid, uint8_t compid, uint32_t time_boot_ms, int32_t lat_e7,
                                                  int32_t lon_e7, int32_t alt_mm, int32_t relative_alt_mm,
                                                  int16_t vx_cm_s, int16_t vy_cm_s, int16_t vz_cm_s, uint16_t hdg_cdeg,
                                                  uint8_t &seq);
  static std::vector<uint8_t> vfr_hud(uint8_t sysid, uint8_t compid, float airspeed_m_s, float groundspeed_m_s,
                                      int16_t heading_deg, uint16_t throttle_pct, float alt_m, float climb_m_s,
                                      uint8_t &seq);
  static std::vector<uint8_t> wind(uint8_t sysid, uint8_t compid, float direction_deg, float speed_m_s,
                                   float speed_z_m_s, uint8_t &seq);
  static std::vector<uint8_t> gps_raw_int(uint8_t sysid, uint8_t compid, int32_t lat_e7, int32_t lon_e7, int32_t alt_mm,
                                          uint8_t fix_type, uint8_t &seq);
  static std::vector<uint8_t> command_long(uint8_t sysid, uint8_t compid, uint16_t command, float param1, uint8_t &seq);
  static std::vector<uint8_t> set_mode(uint8_t sysid, uint8_t compid, uint8_t base_mode, uint32_t custom_mode,
                                       uint8_t &seq);
  static std::vector<uint8_t> mission_current(uint8_t sysid, uint8_t compid, uint16_t mission_seq, uint8_t &seq);
  static std::vector<uint8_t> mission_ack(uint8_t sysid, uint8_t compid, uint8_t mission_type, uint8_t result,
                                          uint8_t &seq);
  static std::vector<uint8_t> mission_count(uint8_t sysid, uint8_t compid, uint16_t count, uint8_t mission_type,
                                            uint8_t &seq);
  static std::vector<uint8_t> mission_item_int(uint8_t sysid, uint8_t compid, uint16_t seq, uint8_t frame,
                                               int32_t lat_e7, int32_t lon_e7, float alt_m, uint8_t &seq_out);
  static std::vector<uint8_t> mission_item_reached(uint8_t sysid, uint8_t compid, uint16_t seq, uint8_t &seq_out);
  static std::vector<uint8_t> distance_sensor(uint8_t sysid, uint8_t compid, float distance_m, uint8_t &seq);
  static std::vector<uint8_t> mission_request_list(uint8_t sysid, uint8_t compid, uint8_t &seq);
  static std::vector<uint8_t> mission_request_int(uint8_t sysid, uint8_t compid, uint16_t mission_seq, uint8_t &seq);
  static std::vector<uint8_t> param_request_read(uint8_t sysid, uint8_t compid, uint16_t param_index,
                                                 const char *param_id, uint8_t &seq);
  static std::vector<uint8_t> param_value(uint8_t sysid, uint8_t compid, const char *param_id, float value,
                                          uint16_t param_index, uint16_t param_count, uint8_t &seq);
  static std::vector<uint8_t> param_set(uint8_t sysid, uint8_t compid, const char *param_id, float value, uint8_t &seq);
  static std::vector<uint8_t> home_position(uint8_t sysid, uint8_t compid, int32_t lat_e7, int32_t lon_e7,
                                            int32_t alt_mm, uint8_t &seq);
  static uint8_t crc_extra_for(uint32_t msgid);
};

} // namespace vrp
