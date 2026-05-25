#pragma once
/**
 * @module  vehicles/VRP_Vehicle
 * @dal     B
 * @req     VRP-LLRD-AP_Vehicle
 * @parity  ArduPilot AP_Vehicle
 * @status  partial
 */

#include <memory>
#include <string>

#include "middleware/params/VRP_Param.h"
#include "middleware/scheduler/Scheduler.h"
#include "middleware/uorb/UORB.h"

namespace vrp {

class Vehicle {
public:
  Vehicle(std::string name, UORB &uorb, VRPParamStore &params);
  virtual ~Vehicle() = default;

  virtual void setup() = 0;
  virtual void loop() = 0;
  virtual std::string mode() const = 0;

  const std::string &name() const { return name_; }
  Scheduler &scheduler() { return scheduler_; }

protected:
  std::string name_;
  UORB &uorb_;
  VRPParamStore &params_;
  Scheduler scheduler_;
};

std::unique_ptr<Vehicle> make_vehicle(const std::string &kind, UORB &uorb, VRPParamStore &params);

} // namespace vrp
