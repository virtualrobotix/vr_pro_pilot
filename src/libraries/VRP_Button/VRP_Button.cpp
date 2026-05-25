#include "libraries/VRP_Button/VRP_Button.h"
#include <sstream>

namespace vrp {

bool VRP_Button::init() { return true; }

ButtonState VRP_Button::update(bool armed, float aux1) {
  ButtonState out{};
  out.id = 1;
  out.pressed = armed && aux1 > 0.5F;
  return out;
}

std::string format_button(const ButtonState &s) {
  std::ostringstream oss;
  oss << "BTN id=" << static_cast<int>(s.id) << " pressed=" << (s.pressed ? 1 : 0);
  return oss.str();
}

} // namespace vrp
