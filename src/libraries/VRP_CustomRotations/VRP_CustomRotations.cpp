#include "libraries/VRP_CustomRotations/VRP_CustomRotations.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_CustomRotations::init() { return true; }

CustomRotationsState VRP_CustomRotations::update(const Attitude &att, bool armed) {
  CustomRotationsState out{};
  if (armed) {
    out.yaw = static_cast<float>(att.yaw_rad * 180.0 / M_PI);
  }
  return out;
}

std::string format_custom_rotations(const CustomRotationsState &s) {
  std::ostringstream oss;
  oss << "CROT yaw=" << s.yaw;
  return oss.str();
}

} // namespace vrp
