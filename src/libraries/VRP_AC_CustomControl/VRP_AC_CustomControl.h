#pragma once
/** @module libraries/VRP_AC_CustomControl @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct CustomControlState {
  bool active{false};
  float roll{0.0F};
  float pitch{0.0F};
};

class VRP_AC_CustomControl {
public:
  bool init();
  CustomControlState update(bool armed, float roll, float pitch);
};

std::string format_custom_control(const CustomControlState &s);

} // namespace vrp
