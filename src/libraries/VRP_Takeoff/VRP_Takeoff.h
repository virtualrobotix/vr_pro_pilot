#pragma once
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

struct TakeoffState {
  bool check_pass{false};
  bool complete{false};
  std::string phase{"idle"};
};

class VRP_Takeoff {
public:
  bool init(double min_throttle = 0.55, double min_climb_m_s = 0.3);
  TakeoffState update(bool armed, float throttle, double vz_m_s, double agl_m, double dt_s);
  void reset();

private:
  double min_throttle_{0.55};
  double min_climb_m_s_{0.3};
  double climb_time_s_{0.0};
};

std::string format_takeoff(const TakeoffState &st);

} // namespace vrp
