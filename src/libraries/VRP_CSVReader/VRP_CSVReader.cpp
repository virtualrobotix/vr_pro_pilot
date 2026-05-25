#include "libraries/VRP_CSVReader/VRP_CSVReader.h"
#include <sstream>

namespace vrp {

bool VRP_CSVReader::init() { return true; }

CsvReaderState VRP_CSVReader::update(uint64_t tick, bool armed) {
  CsvReaderState out{};
  if (armed) {
    out.rows = static_cast<uint32_t>((tick % 100U) + 10U);
  }
  return out;
}

std::string format_csv_reader(const CsvReaderState &s) {
  std::ostringstream oss;
  oss << "CSV rows=" << s.rows;
  return oss.str();
}

} // namespace vrp
