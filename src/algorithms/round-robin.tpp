#ifndef __MINI_TOOLS__ALGORITHMS__ROUND_ROBIN_TPP__
#define __MINI_TOOLS__ALGORITHMS__ROUND_ROBIN_TPP__

#include "algorithms/round-robin.hpp"

namespace mini_tools {
namespace algorithms {

  template <inspector::NUMBER T>
  void RoundRobin::arbitrateNumeric(
    std::queue<RoundRobin::NumericTask<T>> &taskQueue,
    CR<T> valueLimit
  ) {
    while (!taskQueue.empty()) {

      // isolate first item
      NumericTask<T> currentTask = taskQueue.front();
      taskQueue.pop();

      if (currentTask.load > valueLimit) {
        // reduce load
        currentTask.load -= valueLimit;
        taskQueue.push(currentTask);

        // repeated callback
        if (taskQueue.ongoing) taskQueue.ongoing(
          currentTask.load // remaining load
        );
      }
      // task completes with callback
      else if (currentTask.finish) {
        currentTask.finish();
      }
    }
  }

  template <typename T>
  void RoundRobin::arbitrateVector(
    std::queue<VectorTask<T>> &taskQueue,
    CR_SZ sizeLimit
  ) {
    while (!taskQueue.empty()) {

      // isolate first item
      VectorTask<T> currentTask = taskQueue.front();
      taskQueue.pop();

      if (currentTask.load.size() > sizeLimit) {

        // reduce load
        currentTask.load -= sizeLimit;
        taskQueue.push(currentTask);

        VEC<T> wasted;

        utils::VecTools<T>::cutInterval(
          currentTask.load,
          wasted,
          currentTask.load.size() - 1 - sizeLimit,
          currentTask.load.size() - 1
        );

        // repeated callback
        if (taskQueue.ongoing) taskQueue.ongoing(
          wasted // dropped vector
        );
      }
      // task completes with callback
      else if (currentTask.finish) {
        currentTask.finish();
      }
    }
  }
}}

#endif // __MINI_TOOLS__ALGORITHMS__ROUND_ROBIN_TPP__