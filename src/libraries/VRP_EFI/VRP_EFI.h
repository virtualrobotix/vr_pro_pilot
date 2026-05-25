#pragma once
/** @module libraries/VRP_EFI @dal     C @status  partial */
#include <string>

namespace vrp {

struct BatteryStatus;

struct EfiState {
  float fuel{0.0F};
  float flow{0.0F};
};

class VRP_EFI {
public:
  bool init();
  EfiState update(float throttle, bool armed, const BatteryStatus &battery);
};

std::string format_efi(const EfiState &s);

} // namespace vrp
