#include "vehicles/boat/Boat.h"

namespace vrp {

Boat::Boat(UORB &uorb, VRPParamStore &params) : Vehicle("boat", uorb, params) {}

void Boat::setup() {
  params_.set("boat.max_speed_mps", 6.0);
  scheduler_.add_task("boat_nav", 20, [&]() {
    if (auto m = uorb_.subscribe("vehicle/mode")) {
      mode_ = *m;
    }
  });
}

void Boat::loop() {
  if (auto m = uorb_.subscribe("vehicle/mode")) {
    mode_ = *m;
  }
}

std::string Boat::mode() const { return mode_; }

} // namespace vrp
