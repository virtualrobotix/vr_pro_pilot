#pragma once
/**
 * @module  libraries/VRP_Common
 * @dal     B
 * @req     VRP-LLRD-AP_Common
 * @parity  ArduPilot AP_Common
 * @status  partial
 */
/**
 * @module  libraries/VRP_Common
 * @dal     B
 * @req     VRP-LLRD-AP_Common
 * @parity  ArduPilot AP_Common — clean-room BSD rewrite
 */
#include <cstdint>
#include <string>

namespace vrp {

struct ImuSample {
  double ax{0.0};
  double ay{0.0};
  double az{-9.80665};
  double gx{0.0};
  double gy{0.0};
  double gz{0.0};
  uint64_t time_us{0};
};

struct Attitude {
  double roll_rad{0.0};
  double pitch_rad{0.0};
  double yaw_rad{0.0};
};

struct LocalPosition {
  double x{0.0};
  double y{0.0};
  double z{0.0};
  double vx{0.0};
  double vy{0.0};
  double vz{0.0};
  bool valid{false};
};

struct Waypoint {
  double x{0.0};
  double y{0.0};
  double z{0.0};
};

struct BatteryStatus {
  double voltage_v{0.0};
  double remaining_pct{0.0};
  bool valid{false};
};

struct SensorGroundTruth {
  double ax{0.0};
  double ay{0.0};
  double az{-9.80665};
  double gx{0.0};
  double gy{0.0};
  double gz{0.0};
  double yaw_deg{0.0};
};

struct AttitudeSetpoint {
  double roll_rad{0.0};
  double pitch_rad{0.0};
  double yaw_rate_rad_s{0.0};
  double thrust_base{0.55};
};

struct ControlTorque {
  float roll{0.0F};
  float pitch{0.0F};
  float yaw{0.0F};
};

struct MotorOutputQuad {
  float m1{0.0F};
  float m2{0.0F};
  float m3{0.0F};
  float m4{0.0F};
};

struct BoatActuators {
  float left{0.0F};
  float right{0.0F};
};

struct GpsSample {
  double lat_deg{0.0};
  double lon_deg{0.0};
  double alt_m{0.0};
  double speed_m_s{0.0};
  uint8_t fix_type{0};
  bool valid{false};
  uint64_t time_us{0};
};

struct BaroSample {
  double pressure_pa{101325.0};
  double alt_m{0.0};
  bool valid{false};
  uint64_t time_us{0};
};

struct CompassSample {
  double heading_deg{0.0};
  bool valid{false};
  uint64_t time_us{0};
};

struct RcChannels {
  float roll{0.0F};
  float pitch{0.0F};
  float throttle{0.0F};
  float yaw{0.0F};
  float aux1{0.0F};
  float aux2{0.0F};
  float aux3{0.0F};
  float aux4{0.0F};
  bool valid{false};
};

struct VehicleSetpoints {
  AttitudeSetpoint attitude{};
  float boat_forward{0.0F};
  float boat_turn{0.0F};
  float subsea_thrust{0.0F};
  float subsea_yaw{0.0F};
  bool hold_position{true};
  bool use_tecs{false};
  bool use_apm{false};
  double nav_bearing_rad{0.0};
  double nav_speed_m_s{0.0};
  bool nav_active{false};
};

struct WpNavOutput {
  double bearing_rad{0.0};
  double distance_m{0.0};
  double target_speed_m_s{0.0};
  double alt_error_m{0.0};
  bool valid{false};
};

struct ServoOutput {
  uint16_t motor1_us{1000};
  uint16_t motor2_us{1000};
  uint16_t motor3_us{1000};
  uint16_t motor4_us{1000};
  uint16_t tilt_us{1500};
  uint16_t elevon_us{1500};
};

std::string format_wpnav(const WpNavOutput &n);
std::string format_servos(const ServoOutput &s);

std::string format_motors_quad(const MotorOutputQuad &m);

std::string format_imu(const ImuSample &s);
std::string format_attitude(const Attitude &a);
std::string format_local_position(const LocalPosition &p);
std::string format_battery(const BatteryStatus &b);
std::string format_gps(const GpsSample &g);
std::string format_baro(const BaroSample &b);
std::string format_compass(const CompassSample &c);
std::string format_rc(const RcChannels &rc);

} // namespace vrp
