#include "vehicles/vtol/VTOL.h"

namespace vrp {

VTOL::VTOL(UORB &uorb, VRPParamStore &params) : Vehicle("vtol", uorb, params) {}

void VTOL::setup() {
  scheduler_.add_task("vtol_transition", 20, [&]() {
    if (auto m = uorb_.subscribe("vehicle/mode")) {
      mode_ = *m;
    }
  });
}

void VTOL::loop() {
  if (auto m = uorb_.subscribe("vehicle/mode")) {
    mode_ = *m;
  }
}

std::string VTOL::mode() const { return mode_; }

} // namespace vrp
