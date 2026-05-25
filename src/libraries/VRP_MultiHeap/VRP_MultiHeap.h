#pragma once
/** @module libraries/VRP_MultiHeap @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct MultiHeapState {
  uint32_t free_kb{0};
};

class VRP_MultiHeap {
public:
  bool init();
  MultiHeapState status() const;

private:
  uint32_t free_kb_{512};
};

std::string format_multi_heap(const MultiHeapState &s);

} // namespace vrp
