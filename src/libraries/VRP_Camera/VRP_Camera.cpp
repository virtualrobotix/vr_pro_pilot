#include "libraries/VRP_Camera/VRP_Camera.h"

#include <sstream>

namespace vrp {

bool VRP_Camera::init() {
  seq_ = 0;
  return true;
}

CameraState VRP_Camera::update(bool armed, uint64_t tick) {
  CameraState out{};
  out.recording = armed;
  out.frame_count = static_cast<uint32_t>(tick);
  out.valid = true;
  ++seq_;
  (void)seq_;
  return out;
}

std::string format_camera(const CameraState &s) {
  std::ostringstream oss;
  oss << "CAMERA rec=" << (s.recording ? 1 : 0) << " frames=" << s.frame_count << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
