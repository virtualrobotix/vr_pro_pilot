#pragma once
/**
 * @module  modules/control_allocator/ControlAllocator
 * @dal     B
 * @req     VRP-LLRD-AP_Motors
 * @parity  ArduPilot AP_Motors
 * @status  partial
 */

#include <array>
#include <string>

namespace vrp {

class ControlAllocator {
public:
  std::array<float, 4> allocate_quad(float thrust, float yaw) const;
  std::string allocate_boat(float forward, float turn) const;
};

} // namespace vrp
