#include "libraries/VRP_AccelCal/VRP_AccelCal.h"
#include <sstream>

namespace vrp {

bool VRP_AccelCal::init() { return true; }

AccelCalState VRP_AccelCal::update(bool armed, uint64_t tick) {
  AccelCalState out{};
  out.running = armed;
  out.step = armed ? static_cast<uint8_t>((tick % 6) + 1) : 0;
  return out;
}

std::string format_accel_cal(const AccelCalState &s) {
  std::ostringstream oss;
  oss << "ACCELCAL run=" << (s.running ? 1 : 0) << " step=" << static_cast<int>(s.step);
  return oss.str();
}

} // namespace vrp
