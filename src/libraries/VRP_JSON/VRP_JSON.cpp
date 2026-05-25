#include "libraries/VRP_JSON/VRP_JSON.h"
#include <sstream>

namespace vrp {

bool VRP_JSON::init() { return true; }

JsonState VRP_JSON::update(uint64_t tick, bool armed) {
  JsonState out{};
  if (armed) {
    out.keys = static_cast<uint32_t>((tick % 20U) + 4U);
  }
  return out;
}

std::string format_json(const JsonState &s) {
  std::ostringstream oss;
  oss << "JSON keys=" << s.keys;
  return oss.str();
}

} // namespace vrp
