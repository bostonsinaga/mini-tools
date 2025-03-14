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
  mt::VEC_INT numbers = mt_uti::Scanner<int>::txtToNumbers(filenames[0]);
  mt::VEC_INT numbers_copy = numbers;
  std::cout << std::endl;

  // start time
  mt_uti::Timer timer;

  /** Bubble Sort */
  mt_sor::Bubble<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, true, false, filenames[1]);
  timer.print(true, "Bubble Sort:");
  std::cout << std::endl;

  /** Comb Sort */
  mt_sor::Comb<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, true, false, filenames[2]);
  timer.print(true, "Comb Sort:");
  std::cout << std::endl;

  /** Insertion Sort */
  mt_sor::Insertion<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, true, false, filenames[3]);
  timer.print(true, "Insertion Sort:");
  std::cout << std::endl;

  /** Merge Sort */
  mt_sor::Merge<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, true, false, filenames[4]);
  timer.print(true, "Merge Sort:");
  std::cout << std::endl;

  /** Quick Sort */
  mt_sor::Quick<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, true, false, filenames[5]);
  timer.print(true, "Quick Sort:");
  std::cout << std::endl;

  /** Selection Sort */
  mt_sor::Selection<int, int>::solve(numbers, numbers_copy);
  mt_uti::Printer<int>::logf(numbers_copy, true, false, filenames[6]);
  timer.print(true, "Selection Sort:");
  std::cout << std::endl;

  return 0;
}

