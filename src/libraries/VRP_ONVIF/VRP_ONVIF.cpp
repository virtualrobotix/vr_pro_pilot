#include "libraries/VRP_ONVIF/VRP_ONVIF.h"

#include <sstream>

namespace vrp {

bool VRP_ONVIF::init() {
  seq_ = 0;
  return true;
}

OnvifState VRP_ONVIF::update(bool armed, bool gcs_link, uint64_t tick) {
  OnvifState out{};
  out.streaming = armed;
  out.ptz_active = armed && gcs_link;
  out.clients = gcs_link ? 1U : 0U;
  ++seq_;
  (void)tick;
  (void)seq_;
  return out;
}

std::string format_onvif(const OnvifState &s) {
  std::ostringstream oss;
  oss << "ONVIF stream=" << (s.streaming ? 1 : 0) << " ptz=" << (s.ptz_active ? 1 : 0)
      << " clients=" << s.clients;
  return oss.str();
}

} // namespace vrp
