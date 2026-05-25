#include "modules/ekf2/EKF2.h"

#include <sstream>

namespace vrp {

std::string EKF2::update(double x, double y, double z) const {
  std::ostringstream oss;
  oss << "EST_POS x=" << x << " y=" << y << " z=" << z;
  return oss.str();
}

} // namespace vrp
