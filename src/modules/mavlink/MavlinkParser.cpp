#include "modules/mavlink/MavlinkParser.h"

#include "modules/mavlink/MavlinkCodec.h"

namespace vrp {

bool MavlinkParser::parse_v2(const uint8_t *data, size_t len, MavlinkMessage &out) const {
  if (len < 12 || data[0] != 0xFD) {
    return false;
  }
  const uint8_t payload_len = data[1];
  if (len < static_cast<size_t>(12 + payload_len)) {
    return false;
  }

  const uint8_t *payload = data + 10;
  uint8_t crc_buf[280];
  if (payload_len + 9 > sizeof(crc_buf)) {
    return false;
  }
  for (int i = 0; i < 9; ++i) {
    crc_buf[i] = data[1 + i];
  }
  for (uint8_t i = 0; i < payload_len; ++i) {
    crc_buf[9 + i] = payload[i];
  }

  out.msgid = static_cast<uint32_t>(data[7]) | (static_cast<uint32_t>(data[8]) << 8) |
              (static_cast<uint32_t>(data[9]) << 16);
  out.payload.assign(payload, payload + payload_len);

  const uint8_t extra = MavlinkCodec::crc_extra_for(out.msgid);
  if (extra == 0) {
    return false;
  }
  const uint16_t crc = MavlinkCodec::crc_calculate(crc_buf, 9 + payload_len, extra);
  const uint16_t rx_crc = static_cast<uint16_t>(data[10 + payload_len]) |
                          (static_cast<uint16_t>(data[11 + payload_len]) << 8);
  return crc == rx_crc;
}

} // namespace vrp
