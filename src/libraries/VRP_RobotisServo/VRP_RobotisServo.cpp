#include "libraries/VRP_RobotisServo/VRP_RobotisServo.h"

#include <sstream>

namespace vrp {

bool VRP_RobotisServo::init() {
  seq_ = 0;
  return true;
}

RobotisServoState VRP_RobotisServo::update(float command, float load, bool armed) {
  RobotisServoState out{};
  out.valid = armed;
  out.id = armed ? 2 : 0;
  out.position_deg = command * 90.0F;
  out.torque_pct = load * 100.0F;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_robotis_servo(const RobotisServoState &s) {
  std::ostringstream oss;
  oss << "ROBOTIS id=" << static_cast<int>(s.id) << " pos=" << s.position_deg << " torque=" << s.torque_pct
      << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
