#include "libraries/VRP_Stats/VRP_Stats.h"

#include <cmath>
#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Stats::init() {
  loop_count_ = 0;
  armed_ticks_ = 0;
  distance_m_ = 0.0;
  have_prev_ = false;
  return true;
}

void VRP_Stats::update(uint64_t tick, bool armed, const LocalPosition &pos, double dt_s) {
  (void)tick;
  ++loop_count_;
  if (armed) {
    ++armed_ticks_;
    if (have_prev_) {
      const double dx = pos.x - prev_x_;
      const double dy = pos.y - prev_y_;
      distance_m_ += std::sqrt(VRP_Math::sq(dx) + VRP_Math::sq(dy));
    }
    prev_x_ = pos.x;
    prev_y_ = pos.y;
    have_prev_ = true;
  } else {
    have_prev_ = false;
  }
  (void)dt_s;
}

std::string VRP_Stats::summary() const {
  std::ostringstream oss;
  oss << "STATS loops=" << loop_count_ << " armed_ticks=" << armed_ticks_ << " dist_m=" << distance_m_;
  return oss.str();
}

} // namespace vrp
