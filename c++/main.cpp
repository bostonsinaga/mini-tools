#include <chrono>
#include "utils/utils.h"
#include "algorithms/algorithms.h"

int main() {
  // start time
  typedef std::chrono::high_resolution_clock Time;
  typedef std::chrono::milliseconds ms;
  typedef std::chrono::duration<float> fsec;
  auto t0 = Time::now();

  // algorithm test
  std::vector<int> numbers = util::Scanner<int>::txtToNumbers();
  util::Printer<int>::logf(numbers, true, false, "BEFORE");
  sorter::Quick::solve(numbers);
  util::Printer<int>::logf(numbers, true, true, "AFTER");

  // process time
  auto t1 = Time::now();
  fsec fs = t1 - t0;
  ms d = std::chrono::duration_cast<ms>(fs);
  std::cout << "\nDURATIONS:\n" << fs.count() << "s\n" << d.count() << "ms\n";

  return 0;
}

