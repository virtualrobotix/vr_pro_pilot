#pragma once

#include "vehicles/VRP_Vehicle.h"

namespace vrp {

class Quad final : public Vehicle {
public:
  Quad(UORB &uorb, VRPParamStore &params);
  void setup() override;
  void loop() override;
  std::string mode() const override;

private:
  std::string mode_{"Stabilize"};
};

} // namespace vrp
