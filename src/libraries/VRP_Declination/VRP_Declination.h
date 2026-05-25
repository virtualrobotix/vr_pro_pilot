#pragma once
/** @module libraries/VRP_Declination @dal     C @status  partial */
#include <string>

namespace vrp {

struct GpsSample;

struct DeclinationState {
  float deg{0.0F};
};

class VRP_Declination {
public:
  bool init();
  DeclinationState update(const GpsSample &gps);
};

std::string format_declination(const DeclinationState &s);

} // namespace vrp
