#pragma once
/**
 * @module  libraries/VRP_LeakDetector
 * @dal     C
 * @req     VRP-LLRD-AP_LeakDetector
 * @parity  ArduPilot AP_LeakDetector — clean-room BSD rewrite
 * @status  partial
 */
#include <cstdint>
#include <string>

namespace vrp {

struct LeakDetectorState {
  uint8_t sensors{0};
  bool alarm{false};
  bool valid{false};
};

class VRP_LeakDetector {
public:
  bool init();
  LeakDetectorState update(bool armed, double depth_m, uint64_t tick);

private:
  uint32_t seq_{0};
};

std::string format_leak_detector(const LeakDetectorState &s);

} // namespace vrp
