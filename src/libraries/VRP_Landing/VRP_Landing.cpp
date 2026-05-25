#include "libraries/VRP_Landing/VRP_Landing.h"

#include <sstream>

#include "libraries/VRP_Math/VRP_Math.h"

namespace vrp {

bool VRP_Landing::init(double flare_alt_m, double land_alt_m) {
  flare_alt_m_ = flare_alt_m;
  land_alt_m_ = land_alt_m;
  phase_ = "idle";
  bounce_count_ = 0;
  last_agl_ = 999.0;
  return true;
}

void VRP_Landing::reset() {
  phase_ = "approach";
  bounce_count_ = 0;
  last_agl_ = 999.0;
}

LandingSetpoint VRP_Landing::update(const LocalPosition &pos, const RangeFinderSample &rng, double dt_s) {
  (void)dt_s;
  LandingSetpoint sp{};
  sp.phase = phase_;

  if (phase_ == "idle") {
    phase_ = "approach";
    sp.phase = phase_;
  }

  const double agl = rng.valid ? rng.distance_m : -pos.z;
  if (phase_ == "touchdown" && agl > last_agl_ + 0.08) {
    ++bounce_count_;
  }
  last_agl_ = agl;

  if (phase_ == "approach") {
    sp.target_z_m = VRP_Math::clamp(-flare_alt_m_, pos.z - 0.05, -0.5);
    sp.throttle = static_cast<float>(VRP_Math::clamp(0.45 + 0.05 * agl, 0.35, 0.65));
    if (agl <= flare_alt_m_) {
      phase_ = "flare";
    }
  } else if (phase_ == "flare") {
    sp.target_z_m = VRP_Math::clamp(-land_alt_m_, pos.z - 0.08, -0.1);
    sp.throttle = static_cast<float>(VRP_Math::clamp(0.35 + 0.04 * agl, 0.25, 0.5));
    if (agl <= land_alt_m_) {
      phase_ = "touchdown";
    }
  } else if (phase_ == "touchdown") {
    sp.target_z_m = 0.0;
    sp.throttle = bounce_count_ > 1 ? 0.0F : 0.12F;
    sp.land_detector = agl <= land_alt_m_ * 0.6;
    if (sp.land_detector && pos.z > -0.08 && std::abs(pos.vz) < 0.3) {
      phase_ = "complete";
      sp.complete = true;
      sp.request_disarm = true;
      sp.throttle = 0.0F;
    }
  } else {
    sp.complete = true;
    sp.land_detector = true;
    sp.request_disarm = true;
    sp.throttle = 0.0F;
  }

  sp.phase = phase_;
  return sp;
}

std::string format_landing(const LandingSetpoint &sp) {
  std::ostringstream oss;
  oss << "LAND phase=" << sp.phase << " thr=" << sp.throttle << " complete=" << (sp.complete ? 1 : 0)
      << " detector=" << (sp.land_detector ? 1 : 0) << " disarm=" << (sp.request_disarm ? 1 : 0);
  return oss.str();
}

} // namespace vrp
