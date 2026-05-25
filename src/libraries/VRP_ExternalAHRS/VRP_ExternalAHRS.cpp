#include "libraries/VRP_ExternalAHRS/VRP_ExternalAHRS.h"

#include "libraries/VRP_Common/VRP_Common.h"

#include <sstream>

namespace vrp {

bool VRP_ExternalAHRS::init() {
  seq_ = 0;
  return true;
}

ExternalAhrsState VRP_ExternalAHRS::update(const Attitude &att, bool armed) {
  ExternalAhrsState out{};
  out.valid = armed;
  out.roll_deg = att.roll_rad * 180.0 / 3.141592653589793;
  out.pitch_deg = att.pitch_rad * 180.0 / 3.141592653589793;
  out.yaw_deg = att.yaw_rad * 180.0 / 3.141592653589793;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_external_ahrs(const ExternalAhrsState &s) {
  std::ostringstream oss;
  oss << "XAHRS roll=" << static_cast<int>(s.roll_deg) << " pitch=" << static_cast<int>(s.pitch_deg)
      << " yaw=" << static_cast<int>(s.yaw_deg) << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
