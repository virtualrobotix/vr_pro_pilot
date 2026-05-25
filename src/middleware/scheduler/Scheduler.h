#pragma once
/**
 * @module  middleware/scheduler/Scheduler
 * @dal     B
 * @req     VRP-LLRD-AP_Scheduler
 * @parity  ArduPilot AP_Scheduler
 * @status  partial
 */

#include <functional>
#include <string>
#include <vector>

namespace vrp {

struct Task {
  std::string name;
  uint32_t period_ms;
  uint64_t last_run_ms{0};
  std::function<void()> fn;
};

class Scheduler {
public:
  void add_task(const std::string &name, uint32_t period_ms, const std::function<void()> &fn);
  void run(uint64_t now_ms);

private:
  std::vector<Task> tasks_;
};

} // namespace vrp
