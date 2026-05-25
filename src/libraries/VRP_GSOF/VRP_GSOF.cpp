#include "libraries/VRP_GSOF/VRP_GSOF.h"
#include "libraries/VRP_Common/VRP_Common.h"
#include <sstream>

namespace vrp {

bool VRP_GSOF::init() { return true; }

GsofState VRP_GSOF::update(const GpsSample &gps) {
  GsofState out{};
  if (gps.valid) {
    out.fix = gps.fix_type > 0 ? gps.fix_type : 3;
    out.sats = static_cast<uint8_t>(8 + (gps.fix_type % 5));
  }
  return out;
}

std::string format_gsof(const GsofState &s) {
  std::ostringstream oss;
  oss << "GSOF fix=" << static_cast<int>(s.fix) << " sats=" << static_cast<int>(s.sats);
  return oss.str();
}

} // namespace vrp
