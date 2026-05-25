#pragma once
/**
 * @module  libraries/VRP_TECS
 * @dal     B
 * @req     VRP-LLRD-AP_TECS
 * @parity  ArduPilot AP_TECS
 * @status  partial
 */
/**
 * @module  libraries/VRP_TECS
 * @dal     B
 * @req     VRP-LLRD-AP_TECS
 */
namespace vrp {

struct TecsOutput {
  double pitch_rad{0.0};
  double throttle{0.55};
};

class VRP_TECS {
public:
  bool init(double target_alt_m, double target_speed_m_s);
  TecsOutput update(double alt_m, double speed_m_s, double dt_s);

private:
  double target_alt_m_{0.0};
  double target_speed_m_s_{15.0};
};

} // namespace vrp
