#include "libraries/VRP_LeakDetector/VRP_LeakDetector.h"

#include <sstream>

namespace vrp {

bool VRP_LeakDetector::init() {
  seq_ = 0;
  return true;
}

LeakDetectorState VRP_LeakDetector::update(bool armed, double depth_m, uint64_t tick) {
  LeakDetectorState out{};
  out.sensors = armed ? 2 : 0;
  out.valid = armed;
  out.alarm = armed && depth_m > 50.0 && (tick % 500 == 0);
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_leak_detector(const LeakDetectorState &s) {
  std::ostringstream oss;
  oss << "LEAK sensors=" << static_cast<int>(s.sensors) << " alarm=" << (s.alarm ? 1 : 0)
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
