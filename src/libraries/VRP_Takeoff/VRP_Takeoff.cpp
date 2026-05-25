#include "libraries/VRP_Takeoff/VRP_Takeoff.h"

#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Takeoff::init(double min_throttle, double min_climb_m_s) {
  min_throttle_ = min_throttle;
  min_climb_m_s_ = min_climb_m_s;
  climb_time_s_ = 0.0;
  return true;
}

void VRP_Takeoff::reset() { climb_time_s_ = 0.0; }

TakeoffState VRP_Takeoff::update(bool armed, float throttle, double vz_m_s, double agl_m, double dt_s) {
  TakeoffState st{};
  if (!armed) {
    st.phase = "idle";
    return st;
  }
  st.check_pass = static_cast<double>(throttle) >= min_throttle_ && agl_m < 0.5;
  if (st.check_pass && vz_m_s > min_climb_m_s_) {
    climb_time_s_ += dt_s;
  } else if (!st.check_pass) {
    climb_time_s_ = 0.0;
  }
  st.phase = climb_time_s_ > 0.5 ? "climbing" : (st.check_pass ? "spool" : "check");
  st.complete = agl_m > 1.0 || climb_time_s_ > 2.0;
  return st;
}

std::string format_takeoff(const TakeoffState &st) {
  std::ostringstream oss;
  oss << "TAKEOFF phase=" << st.phase << " check=" << (st.check_pass ? 1 : 0)
      << " complete=" << (st.complete ? 1 : 0);
  return oss.str();
}

} // namespace vrp
