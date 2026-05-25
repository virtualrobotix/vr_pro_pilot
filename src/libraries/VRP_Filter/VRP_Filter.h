#pragma once
/**
 * @module  libraries/VRP_Filter
 * @dal     B
 * @req     VRP-LLRD-Filter
 * @parity  ArduPilot Filter
 * @status  partial
 */
/**
 * @module  libraries/VRP_Filter
 * @dal     B
 * @req     VRP-LLRD-Filter
 */
namespace vrp {

class LowPassFilter {
public:
  explicit LowPassFilter(double alpha = 0.9) : alpha_(alpha), initialized_(false), value_(0.0) {}

  double update(double sample) {
    if (!initialized_) {
      value_ = sample;
      initialized_ = true;
      return value_;
    }
    value_ = alpha_ * value_ + (1.0 - alpha_) * sample;
    return value_;
  }

  double value() const { return value_; }

private:
  double alpha_;
  bool initialized_;
  double value_;
};

} // namespace vrp
