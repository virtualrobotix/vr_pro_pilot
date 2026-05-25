#pragma once

#include "vehicles/VRP_Vehicle.h"

namespace vrp {

class Sailboat : public Vehicle {
public:
  Sailboat(UORB &uorb, VRPParamStore &params);
  void setup() override;
  void loop() override;
  std::string mode() const override;

private:
  std::string mode_{"Manual"};
};

} // namespace vrp
