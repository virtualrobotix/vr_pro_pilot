#include "vehicles/quad/Quad.h"

namespace vrp {

Quad::Quad(UORB &uorb, VRPParamStore &params) : Vehicle("quad", uorb, params) {}

void Quad::setup() {
  params_.set("quad.max_tilt_deg", 35.0);
  params_.set("nav.cruise_speed", 5.0);
  params_.set("nav.wp_radius", 2.0);
  params_.set("nav.loiter_radius", 5.0);
  params_.set("control.target_z", -5.0);
  scheduler_.add_task("quad_attitude", 10, [&]() {
    if (auto m = uorb_.subscribe("vehicle/mode")) {
      mode_ = *m;
    }
  });
}

void Quad::loop() {
  if (auto m = uorb_.subscribe("vehicle/mode")) {
    mode_ = *m;
  }
}

std::string Quad::mode() const { return mode_; }

} // namespace vrp
