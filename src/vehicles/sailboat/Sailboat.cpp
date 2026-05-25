#include "vehicles/sailboat/Sailboat.h"

namespace vrp {

Sailboat::Sailboat(UORB &uorb, VRPParamStore &params) : Vehicle("sailboat", uorb, params) {}

void Sailboat::setup() {
  params_.set("sailboat.max_speed_mps", 4.0);
  params_.set("rover.frame_class", 2.0);
  params_.set("rover.skid_steer", 0.0);
  params_.set("sailboat.use_motor", 0.0);
  params_.set("nav.cruise_speed", 1.8);
  params_.set("nav.wp_radius", 3.0);
  scheduler_.add_task("sailboat_nav", 20, [&]() {
    if (auto m = uorb_.subscribe("vehicle/mode")) {
      mode_ = *m;
    }
  });
}

void Sailboat::loop() {
  if (auto m = uorb_.subscribe("vehicle/mode")) {
    mode_ = *m;
  }
}

std::string Sailboat::mode() const { return mode_; }

} // namespace vrp
