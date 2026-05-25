#pragma once

#include "vehicles/VRP_Vehicle.h"

namespace vrp {

class Boat final : public Vehicle {
public:
  Boat(UORB &uorb, VRPParamStore &params);
  void setup() override;
  void loop() override;
  std::string mode() const override;

private:
  std::string mode_{"Manual"};
};

} // namespace vrp
