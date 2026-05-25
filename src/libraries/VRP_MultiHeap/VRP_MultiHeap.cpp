#include "libraries/VRP_MultiHeap/VRP_MultiHeap.h"
#include <sstream>

namespace vrp {

bool VRP_MultiHeap::init() { return true; }

MultiHeapState VRP_MultiHeap::status() const {
  MultiHeapState out{};
  out.free_kb = free_kb_;
  return out;
}

std::string format_multi_heap(const MultiHeapState &s) {
  std::ostringstream oss;
  oss << "MHEAP free_kb=" << s.free_kb;
  return oss.str();
}

} // namespace vrp
