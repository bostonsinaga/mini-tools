#include <filesystem>
#include "../includes/mini-tools.h"

int main() {
  std::filesystem::create_directory("outputs");

  std::string filenames[6] {
    "../resources/sample.txt",
    "outputs/output-bubble-sort.txt",
    "outputs/output-comb-sort.txt",
    "outputs/output-merge-sort.txt",
    "outputs/output-quick-sort.txt",
    "outputs/output-selection-sort.txt"
  };

  // read input
  mt::VEC_INT numbers = mt_uti::Scanner<int>::txtToNumbers(filenames[0]);
  std::cout << std::endl;

  /** Bubble Sort */
  mt_uti::Timer timer;
  mt_uti::Printer<int>::logf(
    mt_alg::sorters::Bubble<int>::solve(numbers),
    true, false, filenames[1]
  );
  timer.print(true, "Bubble Sort:");
  std::cout << std::endl;

  /** Comb Sort */
  timer.reset();
  mt_uti::Printer<int>::logf(
    mt_alg::sorters::Comb<int>::solve(numbers),
    true, false, filenames[2]
  );
  timer.print(true, "Comb Sort:");
  std::cout << std::endl;

  /** Merge Sort */
  timer.reset();
  mt_uti::Printer<int>::logf(
    mt_alg::sorters::Merge<int>::solve(numbers),
    true, false, filenames[3]
  );
  timer.print(true, "Merge Sort:");
  std::cout << std::endl;

  /** Quick Sort */
  timer.reset();
  mt_uti::Printer<int>::logf(
    mt_alg::sorters::Quick<int>::solve(numbers),
    true, false, filenames[4]
  );
  timer.print(true, "Quick Sort:");
  std::cout << std::endl;

  /** Selection Sort */
  timer.reset();
  mt_uti::Printer<int>::logf(
    mt_alg::sorters::Selection<int>::solve(numbers),
    true, false, filenames[5]
  );
  timer.print(true, "Selection Sort:");
  std::cout << std::endl;

  return 0;
}

