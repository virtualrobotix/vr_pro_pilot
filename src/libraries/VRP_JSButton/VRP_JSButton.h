#pragma once
/** @module libraries/VRP_JSButton @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct RcChannels;

struct JsButtonState {
  uint8_t btn{0};
};

class VRP_JSButton {
public:
  bool init();
  JsButtonState update(const RcChannels &rc, bool armed);
};

std::string format_js_button(const JsButtonState &s);

} // namespace vrp
