#include "middleware/scheduler/Scheduler.h"

namespace vrp {

void Scheduler::add_task(const std::string &name, uint32_t period_ms, const std::function<void()> &fn) {
  tasks_.push_back({name, period_ms, 0, fn});
}

void Scheduler::run(uint64_t now_ms) {
  for (auto &task : tasks_) {
    if (task.last_run_ms == 0 || now_ms - task.last_run_ms >= task.period_ms) {
      task.fn();
      task.last_run_ms = now_ms;
    }
  }
}

} // namespace vrp
