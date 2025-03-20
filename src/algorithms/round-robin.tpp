#include <iostream>
#include <queue>
#include <vector>
#include <string>

struct Task {
  int id;              // Task ID
  int executionTime;   // Time required to complete the task
};

int main() {
  // Example tasks with their execution times
  std::vector<Task> tasks = {{1, 5}, {2, 10}, {3, 8}, {4, 4}};
  int timeSlice = 3;  // Time slice for each task

  std::queue<Task> taskQueue;

  // Load all tasks into the queue
  for (const auto& task : tasks) {
      taskQueue.push(task);
  }

  std::cout << "Round-Robin Scheduling Simulation:\n";

  // Simulate the Round-Robin process
  while (!taskQueue.empty()) {
    Task currentTask = taskQueue.front();
    taskQueue.pop();

    std::cout << "Processing Task " << currentTask.id;

    if (currentTask.executionTime > timeSlice) {
      std::cout << " for " << timeSlice << " units of time.\n";
      currentTask.executionTime -= timeSlice;
      taskQueue.push(currentTask); // Re-add the task for further processing
    } else {
      std::cout << " for " << currentTask.executionTime << " units of time (Task Complete).\n";
    }
  }

  std::cout << "All tasks completed.\n";
  return 0;
}
