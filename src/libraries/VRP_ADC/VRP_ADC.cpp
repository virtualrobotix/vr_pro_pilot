#include "libraries/VRP_ADC/VRP_ADC.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include <sstream>

namespace vrp {

bool VRP_ADC::init() { return true; }

AdcState VRP_ADC::update(const BatteryStatus &battery, bool armed) {
  AdcState out{};
  if (armed && battery.valid) {
    out.ch = 1;
    out.mv = static_cast<float>(battery.voltage_v * 1000.0);
  }
  return out;
}

std::string format_adc(const AdcState &s) {
  std::ostringstream oss;
  oss << "ADC ch=" << static_cast<int>(s.ch) << " mv=" << s.mv;
  return oss.str();
}

} // namespace vrp
