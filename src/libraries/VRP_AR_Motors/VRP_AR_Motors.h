#pragma once
/**
 * @module  libraries/VRP_AR_Motors
 * @dal     B
 * @req     VRP-LLRD-AR_Motors
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

enum class ArFrameClass : uint8_t { Rover = 1, Boat = 2, BalanceBot = 3 };

struct ArMotorsState {
  float left{0.0F};
  float right{0.0F};
  float throttle{0.0F};
  float steering{0.0F};
  bool active{false};
  ArFrameClass frame{ArFrameClass::Boat};
};

class VRP_AR_Motors {
public:
  bool init(ArFrameClass frame = ArFrameClass::Boat, bool skid_steering = true);
  ArMotorsState update(float throttle, float steering, bool armed);

private:
  ArFrameClass frame_{ArFrameClass::Boat};
  bool skid_steering_{true};
  float last_throttle_{0.0F};
  float last_steering_{0.0F};
  float slew_rate_{2.0F};
};

std::string format_ar_motors(const ArMotorsState &s);

} // namespace vrp
