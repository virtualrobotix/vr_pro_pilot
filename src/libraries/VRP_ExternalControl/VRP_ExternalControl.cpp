#include "libraries/VRP_ExternalControl/VRP_ExternalControl.h"
#include <sstream>

namespace vrp {

bool VRP_ExternalControl::init() { return true; }

ExternalControlState VRP_ExternalControl::update(bool armed, bool gcs_link) {
  ExternalControlState out{};
  out.active = armed && gcs_link;
  return out;
}

std::string format_external_control(const ExternalControlState &s) {
  std::ostringstream oss;
  oss << "EXTCTL active=" << (s.active ? 1 : 0);
  return oss.str();
}

} // namespace vrp
