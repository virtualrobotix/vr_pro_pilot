#include "libraries/VRP_Terrain/VRP_Terrain.h"

#include <cmath>
#include <sstream>

namespace vrp {

bool VRP_Terrain::init() {
  base_m_ = 120.0;
  return true;
}

TerrainSample VRP_Terrain::height_at(double lat_deg, double lon_deg) {
  TerrainSample out{};
  out.height_amsl_m = base_m_ + std::sin(lat_deg * 12.0) * 8.0 + std::cos(lon_deg * 10.0) * 6.0;
  out.valid = true;
  return out;
}

std::string format_terrain(const TerrainSample &s) {
  std::ostringstream oss;
  oss << "TERRAIN amsl=" << s.height_amsl_m << " valid=" << (s.valid ? 1 : 0);
  return oss.str();
}

} // namespace vrp
