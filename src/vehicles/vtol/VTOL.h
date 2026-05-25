#pragma once

#include "vehicles/VRP_Vehicle.h"

namespace vrp {

class VTOL final : public Vehicle {
public:
  VTOL(UORB &uorb, VRPParamStore &params);
  void setup() override;
  void loop() override;
  std::string mode() const override;

private:
  std::string mode_{"QStabilize"};
};

} // namespace vrp
