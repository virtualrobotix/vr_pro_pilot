#pragma once
/** @module libraries/VRP_ExternalControl @dal     C @status  partial */
#include <string>

namespace vrp {

struct ExternalControlState {
  bool active{false};
};

class VRP_ExternalControl {
public:
  bool init();
  ExternalControlState update(bool armed, bool gcs_link);
};

std::string format_external_control(const ExternalControlState &s);

} // namespace vrp
