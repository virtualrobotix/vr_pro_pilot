#pragma once

#include "vehicles/VRP_Vehicle.h"

namespace vrp {

class Subsea final : public Vehicle {
public:
  Subsea(UORB &uorb, VRPParamStore &params);
  void setup() override;
  void loop() override;
  std::string mode() const override;

private:
  std::string mode_{"DepthHold"};
};

} // namespace vrp
