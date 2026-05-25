#include "libraries/VRP_Parachute/VRP_Parachute.h"

#include <sstream>

namespace vrp {

bool VRP_Parachute::init() {
  deployed_ = false;
  released_ = false;
  return true;
}

bool VRP_Parachute::update(bool deploy_request, double alt_m) {
  if (deploy_request && alt_m > 0.01) {
    deployed_ = true;
    released_ = true;
  }
  return deployed_;
}

std::string format_parachute(bool deployed, bool released) {
  std::ostringstream oss;
  oss << "PARACHUTE deployed=" << (deployed ? 1 : 0) << " released=" << (released ? 1 : 0);
  return oss.str();
}

} // namespace vrp
