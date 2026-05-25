#pragma once
/**
 * @module  libraries/VRP_Camera
 * @dal     C
 * @req     VRP-LLRD-AP_Camera
 * @parity  ArduPilot AP_Camera — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct CameraState {
  bool recording{false};
  uint32_t frame_count{0};
  bool valid{false};
};

class VRP_Camera {
public:
  bool init();
  CameraState update(bool armed, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_camera(const CameraState &s);

} // namespace vrp
