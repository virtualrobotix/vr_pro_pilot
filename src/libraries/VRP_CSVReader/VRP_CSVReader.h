#pragma once
/** @module libraries/VRP_CSVReader @dal     C @status  partial */
#include <cstdint>
#include <string>

namespace vrp {

struct CsvReaderState {
  uint32_t rows{0};
};

class VRP_CSVReader {
public:
  bool init();
  CsvReaderState update(uint64_t tick, bool armed);
};

std::string format_csv_reader(const CsvReaderState &s);

} // namespace vrp
