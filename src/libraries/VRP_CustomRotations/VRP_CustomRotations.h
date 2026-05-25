#pragma once
/** @module libraries/VRP_CustomRotations @dal     C @status  partial */
#include <string>

namespace vrp {

struct Attitude;

struct CustomRotationsState {
  float yaw{0.0F};
};

class VRP_CustomRotations {
public:
  bool init();
  CustomRotationsState update(const Attitude &att, bool armed);
};

std::string format_custom_rotations(const CustomRotationsState &s);

} // namespace vrp
