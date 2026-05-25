#pragma once
/**
 * @module  libraries/VRP_Math
 * @dal     B
 * @req     VRP-LLRD-AP_Math
 * @parity  ArduPilot AP_Math
 * @status  partial
 */
/**
 * @module  libraries/VRP_Math
 * @dal     B
 * @req     VRP-LLRD-AP_Math
 */
#include <cmath>

namespace vrp {

struct VRP_Math {
  static constexpr double kPi = 3.14159265358979323846;
  static constexpr double kDegToRad = kPi / 180.0;
  static constexpr double kRadToDeg = 180.0 / kPi;

  static double deg_to_rad(double deg) { return deg * kDegToRad; }
  static double rad_to_deg(double rad) { return rad * kRadToDeg; }

  static double clamp(double v, double lo, double hi) {
    if (v < lo) {
      return lo;
    }
    if (v > hi) {
      return hi;
    }
    return v;
  }

  static double wrap_pi(double rad) {
    while (rad > kPi) {
      rad -= 2.0 * kPi;
    }
    while (rad < -kPi) {
      rad += 2.0 * kPi;
    }
    return rad;
  }

  static double sq(double v) { return v * v; }
};

} // namespace vrp
