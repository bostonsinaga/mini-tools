#include <filesystem>
#include "mini-tools.h"

int main() {
  std::filesystem::create_directory("outputs");

  std::string filenames[7] {
    "res/sample.txt",
    "outputs/output-bubble-sort.txt",
    "outputs/output-comb-sort.txt",
    "outputs/output-insertion-sort.txt",
    "outputs/output-merge-sort.txt",
    "outputs/output-quick-sort.txt",
    "outputs/output-selection-sort.txt"
  };

  // read input
  mt::VEC_INT numbers = mt_uti::Scanner::txtToNumbers<int>(filenames[0]);
  mt::VEC_INT numbers_copy = numbers;
  std::cout << std::endl;

  // start time
  mt_uti::Timer timer;

  /** Bubble Sort */
  mt_alg::sorters::Bubble<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, filenames[1], true, false);
  timer.print(true, "Bubble Sort:");
  std::cout << std::endl;

  /** Comb Sort */
  mt_alg::sorters::Comb<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, filenames[2], true, false);
  timer.print(true, "Comb Sort:");
  std::cout << std::endl;

  /** Insertion Sort */
  mt_alg::sorters::Insertion<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, filenames[3], true, false);
  timer.print(true, "Insertion Sort:");
  std::cout << std::endl;

  /** Merge Sort */
  mt_alg::sorters::Merge<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, filenames[4], true, false);
  timer.print(true, "Merge Sort:");
  std::cout << std::endl;

  /** Quick Sort */
  mt_alg::sorters::Quick<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, filenames[5], true, false);
  timer.print(true, "Quick Sort:");
  std::cout << std::endl;

  /** Selection Sort */
  mt_alg::sorters::Selection<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, filenames[6], true, false);
  timer.print(true, "Selection Sort:");
  std::cout << std::endl;

  return 0;
}

