#include "libraries/VRP_InternalError/VRP_InternalError.h"

#include <sstream>

namespace vrp {

bool VRP_InternalError::init() {
  count_ = 0;
  return true;
}

InternalErrorState VRP_InternalError::update(bool armed, uint64_t tick) {
  InternalErrorState out{};
  out.code = 0;
  out.count = count_;
  out.fault = false;
  if (armed) {
    ++count_;
  }
  out.count = count_;
  (void)tick;
  return out;
}

std::string format_internal_error(const InternalErrorState &s) {
  std::ostringstream oss;
  oss << "INTERR code=" << s.code << " count=" << s.count << " fault=" << (s.fault ? 1 : 0);
  return oss.str();
}

} // namespace vrp
