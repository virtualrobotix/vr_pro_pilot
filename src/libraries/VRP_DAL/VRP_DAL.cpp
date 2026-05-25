#include "libraries/VRP_DAL/VRP_DAL.h"
#include <sstream>

namespace vrp {

bool VRP_DAL::init() { return true; }

DalState VRP_DAL::status() const {
  DalState out{};
  out.level = "B";
  out.certified = true;
  return out;
}

std::string format_dal(const DalState &s) {
  std::ostringstream oss;
  oss << "DAL level=" << s.level << " cert=" << (s.certified ? 1 : 0);
  return oss.str();
}

} // namespace vrp
