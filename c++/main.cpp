
#include <ctime>

#include "utils/printer.h"
#include "utils/reader.h"
#include "algorithms/bubble-sort.h"

int main() {
  time_t startTime = std::time(0);
  std::vector<int> numbers = utils::Reader::txtToNumbers();

  /** Algorithm test */

  // ...

  // process time
  std::cout << "\n\nDURATION: " << std::time(0) - startTime;

  return 0;
}

