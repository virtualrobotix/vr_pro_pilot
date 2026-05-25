#pragma once
/** @module libraries/VRP_GSOF @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct GpsSample;

struct GsofState {
  uint8_t fix{0};
  uint8_t sats{0};
};

class VRP_GSOF {
public:
  bool init();
  GsofState update(const GpsSample &gps);
};

std::string format_gsof(const GsofState &s);

} // namespace vrp
