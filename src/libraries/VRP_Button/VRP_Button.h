#pragma once
/** @module libraries/VRP_Button @dal     D @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct ButtonState {
  uint8_t id{0};
  bool pressed{false};
};

class VRP_Button {
public:
  bool init();
  ButtonState update(bool armed, float aux1);
};

std::string format_button(const ButtonState &s);

} // namespace vrp
