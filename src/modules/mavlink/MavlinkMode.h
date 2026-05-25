#pragma once

#include <cstdint>
#include <string>

namespace vrp {

std::string mavlink_mode_from_custom(const std::string &vehicle, uint32_t custom_mode);

} // namespace vrp
