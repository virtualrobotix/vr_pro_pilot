#pragma once
/**
 * @module  libraries/VRP_Terrain
 * @dal     C
 * @req     VRP-LLRD-AP_Terrain
 * @parity  ArduPilot AP_Terrain — clean-room BSD rewrite
 * @status  partial
 */
#include <string>

namespace vrp {

struct TerrainSample {
  double height_amsl_m{0.0};
  bool valid{false};
};

class VRP_Terrain {
public:
  bool init();
  TerrainSample height_at(double lat_deg, double lon_deg);

private:
  double base_m_{120.0};
};

std::string format_terrain(const TerrainSample &s);

} // namespace vrp
