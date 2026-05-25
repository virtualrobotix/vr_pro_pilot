#include "libraries/VRP_EFI/VRP_EFI.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include <sstream>

namespace vrp {

bool VRP_EFI::init() { return true; }

EfiState VRP_EFI::update(float throttle, bool armed, const BatteryStatus &battery) {
  EfiState out{};
  if (armed) {
    out.fuel = battery.valid ? static_cast<float>(battery.remaining_pct) : 100.0F;
    out.flow = throttle * 12.0F;
  }
  return out;
}

std::string format_efi(const EfiState &s) {
  std::ostringstream oss;
  oss << "EFI fuel=" << s.fuel << " flow=" << s.flow;
  return oss.str();
}

} // namespace vrp
