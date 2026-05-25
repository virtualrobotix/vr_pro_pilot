#pragma once
/**
 * @module  libraries/VRP_GPS
 * @dal     B
 * @req     VRP-LLRD-AP_GPS
 * @parity  ArduPilot AP_GPS
 * @status  partial
 */
/**
 * @module  libraries/VRP_GPS
 * @dal     B
 * @req     VRP-LLRD-AP_GPS
 */
#include "libraries/VRP_Common/VRP_Common.h"

namespace vrp {

struct GpsInput {
  double x_m{0.0};
  double y_m{0.0};
  double z_m{0.0};
  double speed_m_s{0.0};
};

class VRP_GPS {
public:
  bool init(double origin_lat_deg, double origin_lon_deg);
  GpsSample update(const GpsInput &in, uint64_t time_us);

private:
  double origin_lat_deg_{45.0};
  double origin_lon_deg_{9.0};
};

} // namespace vrp
