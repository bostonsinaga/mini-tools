#include <chrono>
#include "includes/mini-tools.h"

int main() {
  // start time
  typedef std::chrono::high_resolution_clock Time;
  typedef std::chrono::milliseconds ms;
  typedef std::chrono::duration<float> fsec;
  auto t0 = Time::now();

  std::string
    filename_seeds = "resources/sample.txt",
    filename_sorted = "resources/output.txt";

  // algorithm test
  mt::VEC_INT numbers = mt_uti::Scanner<int>::txtToNumbers(filename_seeds);
  mt_uti::Printer<int>::logf(numbers, true, false, filename_sorted, "BEFORE");
  mt_alg_sort::Quick::solve(numbers);
  mt_uti::Printer<int>::logf(numbers, true, true, filename_sorted, "AFTER");

  // process time
  auto t1 = Time::now();
  fsec fs = t1 - t0;
  ms d = std::chrono::duration_cast<ms>(fs);
  std::cout << "\nDURATIONS:\n" << fs.count() << "s\n" << d.count() << "ms\n";

  return 0;
}

