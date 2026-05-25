#include "libraries/VRP_Common/VRP_Common.h"

#include <sstream>

namespace vrp {

std::string format_imu(const ImuSample &s) {
  std::ostringstream oss;
  oss << "IMU ax=" << s.ax << " ay=" << s.ay << " az=" << s.az << " gx=" << s.gx << " gy=" << s.gy
      << " gz=" << s.gz << " t_us=" << s.time_us;
  return oss.str();
}

std::string format_attitude(const Attitude &a) {
  std::ostringstream oss;
  oss << "ATT roll=" << a.roll_rad << " pitch=" << a.pitch_rad << " yaw=" << a.yaw_rad;
  return oss.str();
}

std::string format_local_position(const LocalPosition &p) {
  std::ostringstream oss;
  oss << "EST_POS x=" << p.x << " y=" << p.y << " z=" << p.z << " vx=" << p.vx << " vy=" << p.vy
      << " vz=" << p.vz << " valid=" << (p.valid ? 1 : 0);
  return oss.str();
}

std::string format_battery(const BatteryStatus &b) {
  std::ostringstream oss;
  oss << "BATT v=" << b.voltage_v << " pct=" << b.remaining_pct << " valid=" << (b.valid ? 1 : 0);
  return oss.str();
}

std::string format_motors_quad(const MotorOutputQuad &m) {
  std::ostringstream oss;
  oss << "MOTORS m1=" << m.m1 << " m2=" << m.m2 << " m3=" << m.m3 << " m4=" << m.m4;
  return oss.str();
}

std::string format_gps(const GpsSample &g) {
  std::ostringstream oss;
  oss << "GPS lat=" << g.lat_deg << " lon=" << g.lon_deg << " alt=" << g.alt_m << " fix=" << static_cast<int>(g.fix_type)
      << " valid=" << (g.valid ? 1 : 0);
  return oss.str();
}

std::string format_baro(const BaroSample &b) {
  std::ostringstream oss;
  oss << "BARO alt=" << b.alt_m << " press=" << b.pressure_pa << " valid=" << (b.valid ? 1 : 0);
  return oss.str();
}

std::string format_compass(const CompassSample &c) {
  std::ostringstream oss;
  oss << "COMPASS hdg=" << c.heading_deg << " valid=" << (c.valid ? 1 : 0);
  return oss.str();
}

std::string format_rc(const RcChannels &rc) {
  std::ostringstream oss;
  oss << "RC roll=" << rc.roll << " pitch=" << rc.pitch << " thr=" << rc.throttle << " yaw=" << rc.yaw
      << " aux1=" << rc.aux1 << " aux2=" << rc.aux2;
  return oss.str();
}

std::string format_wpnav(const WpNavOutput &n) {
  std::ostringstream oss;
  oss << "WPNAV brg=" << n.bearing_rad << " dist=" << n.distance_m << " spd=" << n.target_speed_m_s
      << " trn=" << n.turn_rate_rad_s << " valid=" << (n.valid ? 1 : 0);
  return oss.str();
}

std::string format_servos(const ServoOutput &s) {
  std::ostringstream oss;
  oss << "SRV m1=" << s.motor1_us << " m2=" << s.motor2_us << " m3=" << s.motor3_us << " m4=" << s.motor4_us
      << " tilt=" << s.tilt_us;
  return oss.str();
}

bool is_ar_surface_vehicle(const std::string &vehicle) {
  return vehicle == "boat" || vehicle == "rover" || vehicle == "sailboat";
}

uint8_t mavlink_type_for_vehicle(const std::string &vehicle) {
  if (vehicle == "boat" || vehicle == "sailboat") {
    return 11U;
  }
  if (vehicle == "rover") {
    return 10U;
  }
  if (vehicle == "vtol") {
    return 22U;
  }
  if (vehicle == "subsea") {
    return 12U;
  }
  return 2U;
}

} // namespace vrp
