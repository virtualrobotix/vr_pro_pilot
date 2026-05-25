#pragma once

#include <cstdint>
#include <string>

namespace vrp {

std::string mavlink_mode_from_custom(const std::string &vehicle, uint32_t custom_mode);
uint32_t mavlink_custom_mode_from_mode(const std::string &vehicle, const std::string &mode);

} // namespace vrp
