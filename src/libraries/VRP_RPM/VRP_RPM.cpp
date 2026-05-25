#include "libraries/VRP_RPM/VRP_RPM.h"

#include <sstream>

namespace vrp {

bool VRP_RPM::init() {
  scale_ = 9800.0;
  return true;
}

RpmSample VRP_RPM::update(float throttle) {
  RpmSample out{};
  const double base = static_cast<double>(throttle) * scale_;
  for (size_t i = 0; i < out.rpm.size(); ++i) {
    out.rpm[i] = base * (1.0 + static_cast<double>(i) * 0.01);
  }
  out.valid = throttle > 0.05F;
  return out;
}

std::string format_rpm(const RpmSample &s) {
  std::ostringstream oss;
  oss << "RPM m1=" << s.rpm[0] << " m4=" << s.rpm[3] << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
