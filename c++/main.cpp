
#include <chrono>

#include "utils/printer.h"
#include "utils/reader.h"
#include "algorithms/bubble-sort.h"
#include "algorithms/quick-sort.h"

int main() {
  /** Start Time */

  typedef std::chrono::high_resolution_clock Time;
  typedef std::chrono::milliseconds ms;
  typedef std::chrono::duration<float> fsec;
  auto t0 = Time::now();

  /** Algorithm Test */

  std::vector<int> numbers = util::Reader::txtToNumbers();

  util::Printer::log(numbers, util::Printer::BAR_STYLE, "BEFORE");
  std::cout << std::endl;

  sorter::Quick::solve(numbers);

  util::Printer::log(numbers, util::Printer::BAR_STYLE, "AFTER");

  /** Process Time */

  auto t1 = Time::now();
  fsec fs = t1 - t0;
  ms d = std::chrono::duration_cast<ms>(fs);
  std::cout << "\nDURATIONS:\n" << fs.count() << "s\n" << d.count() << "ms\n";

  return 0;
}

