#pragma once
/** @module libraries/VRP_DAL @dal     B @status  partial */
#include <string>

namespace vrp {

struct DalState {
  const char *level{"B"};
  bool certified{false};
};

class VRP_DAL {
public:
  bool init();
  DalState status() const;
};

std::string format_dal(const DalState &s);

} // namespace vrp
