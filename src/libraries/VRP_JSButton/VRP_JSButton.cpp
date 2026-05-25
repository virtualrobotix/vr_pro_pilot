#include "libraries/VRP_JSButton/VRP_JSButton.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include <sstream>

namespace vrp {

bool VRP_JSButton::init() { return true; }

JsButtonState VRP_JSButton::update(const RcChannels &rc, bool armed) {
  JsButtonState out{};
  if (armed && rc.valid) {
    out.btn = rc.aux3 > 0.5F ? 2 : 1;
  }
  return out;
}

std::string format_js_button(const JsButtonState &s) {
  std::ostringstream oss;
  oss << "JSBTN btn=" << static_cast<int>(s.btn);
  return oss.str();
}

} // namespace vrp
