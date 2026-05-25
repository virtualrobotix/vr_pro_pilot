#include "vehicles/VRP_Vehicle.h"

#include <memory>
#include <stdexcept>

#include "vehicles/boat/Boat.h"
#include "vehicles/quad/Quad.h"
#include "vehicles/subsea/Subsea.h"
#include "vehicles/vtol/VTOL.h"

namespace vrp {

Vehicle::Vehicle(std::string name, UORB &uorb, VRPParamStore &params)
    : name_(std::move(name)), uorb_(uorb), params_(params) {}

std::unique_ptr<Vehicle> make_vehicle(const std::string &kind, UORB &uorb, VRPParamStore &params) {
  if (kind == "quad") {
    return std::make_unique<Quad>(uorb, params);
  }
  if (kind == "boat") {
    return std::make_unique<Boat>(uorb, params);
  }
  if (kind == "vtol") {
    return std::make_unique<VTOL>(uorb, params);
  }
  if (kind == "subsea") {
    return std::make_unique<Subsea>(uorb, params);
  }
  throw std::runtime_error("unsupported vehicle: " + kind);
}

} // namespace vrp
