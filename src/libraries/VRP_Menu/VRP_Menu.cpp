#include "libraries/VRP_Menu/VRP_Menu.h"

#include <sstream>

namespace vrp {

bool VRP_Menu::init() {
  item_ = 0;
  return true;
}

std::string VRP_Menu::update(uint64_t tick, bool armed) {
  if (!armed) {
    item_ = tick % 4U;
  }
  std::ostringstream oss;
  oss << "MENU item=" << item_ << " armed=" << (armed ? 1 : 0);
  return oss.str();
}

} // namespace vrp
