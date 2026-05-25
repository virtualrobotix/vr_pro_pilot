#include "vehicles/subsea/Subsea.h"

namespace vrp {

Subsea::Subsea(UORB &uorb, VRPParamStore &params) : Vehicle("subsea", uorb, params) {}

void Subsea::setup() {
  scheduler_.add_task("subsea_depth", 20, [&]() {
    if (auto m = uorb_.subscribe("vehicle/mode")) {
      mode_ = *m;
    }
  });
}

void Subsea::loop() {
  if (auto m = uorb_.subscribe("vehicle/mode")) {
    mode_ = *m;
  }
}

std::string Subsea::mode() const { return mode_; }

} // namespace vrp
