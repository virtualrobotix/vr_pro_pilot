#include "vehicles/rover/Rover.h"

namespace vrp {

Rover::Rover(UORB &uorb, VRPParamStore &params) : Vehicle("rover", uorb, params) {}

void Rover::setup() {
  params_.set("rover.max_speed_mps", 4.0);
  params_.set("rover.frame_class", 1.0);
  params_.set("rover.skid_steer", 1.0);
  params_.set("nav.cruise_speed", 1.5);
  params_.set("nav.wp_radius", 1.5);
  scheduler_.add_task("rover_nav", 20, [&]() {
    if (auto m = uorb_.subscribe("vehicle/mode")) {
      mode_ = *m;
    }
  });
}

void Rover::loop() {
  if (auto m = uorb_.subscribe("vehicle/mode")) {
    mode_ = *m;
  }
}

std::string Rover::mode() const { return mode_; }

} // namespace vrp
