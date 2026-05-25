#include "libraries/VRP_GPS/VRP_GPS.h"

namespace vrp {

bool VRP_GPS::init(double origin_lat_deg, double origin_lon_deg) {
  origin_lat_deg_ = origin_lat_deg;
  origin_lon_deg_ = origin_lon_deg;
  return true;
}

GpsSample VRP_GPS::update(const GpsInput &in, uint64_t time_us) {
  GpsSample out{};
  out.lat_deg = origin_lat_deg_ + in.y_m / 111320.0;
  out.lon_deg = origin_lon_deg_ + in.x_m / 111320.0;
  out.alt_m = -in.z_m;
  out.speed_m_s = in.speed_m_s;
  out.fix_type = 3;
  out.valid = true;
  out.time_us = time_us;
  return out;
}

} // namespace vrp
