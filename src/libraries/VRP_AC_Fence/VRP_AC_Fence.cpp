#include "libraries/VRP_AC_Fence/VRP_AC_Fence.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_AC_Fence::init(double center_x, double center_y, double radius_m, double min_z, double max_z) {
  cx_ = center_x;
  cy_ = center_y;
  radius_m_ = radius_m;
  min_z_ = min_z;
  max_z_ = max_z;
  return true;
}

FenceStatus VRP_AC_Fence::check(const LocalPosition &pos, std::string &detail) const {
  if (!pos.valid) {
    detail = "FENCE skip invalid pos";
    return FenceStatus::Ok;
  }
  const double dx = pos.x - cx_;
  const double dy = pos.y - cy_;
  const double dist = std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
  if (dist > radius_m_) {
    std::ostringstream oss;
    oss << "FENCE breach horizontal dist=" << dist << " max=" << radius_m_;
    detail = oss.str();
    return FenceStatus::Breach;
  }
  if (pos.z < min_z_ || pos.z > max_z_) {
    std::ostringstream oss;
    oss << "FENCE breach altitude z=" << pos.z << " limits=[" << min_z_ << "," << max_z_ << "]";
    detail = oss.str();
    return FenceStatus::Breach;
  }
  detail = "FENCE ok";
  return FenceStatus::Ok;
}

} // namespace vrp
