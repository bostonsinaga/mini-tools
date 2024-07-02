#ifndef __ALGORITHMS__SORTERS__QUICK_SORT_CPP__
#define __ALGORITHMS__SORTERS__QUICK_SORT_CPP__

#include <ctime>

namespace mini_tools {
namespace algorithms {
namespace sorters {

  /** Lomuto Partitioning */
  template <typename T>
  int Quick<T>::lomutoPartition(
    std::vector<T> *messy,
    CR_INT low,
    CR_INT high,
    bool &ascending
  ) {
    int i = low - 1;

    for (int j = low; j < high; j++) {
      if ((ascending && messy->at(j) < messy->at(high)) ||
        (!ascending && messy->at(j) > messy->at(high))
      ) {
        i++;
        std::swap(messy->at(i), messy->at(j));
      }
    }

    std::swap(messy->at(i+1), messy->at(high));
    return i+1;
  }

  template <typename T>
  int Quick<T>::randomPartition(
    std::vector<T> *messy,
    CR_INT low,
    CR_INT high,
    bool &ascending
  ) {
    std::srand(std::time(NULL));
    int random = low + std::rand() % (high - low);
    std::swap(messy->at(random), messy->at(high));
    return Quick<T>::lomutoPartition(messy, low, high, ascending);
  }

  template <typename T>
  void Quick<T>::recursion(
    std::vector<T> *messy,
    CR_INT low,
    CR_INT high,
    bool &ascending
  ) {
    if (low < high) {
      int piv = randomPartition(messy, low, high, ascending);
      // int piv = lomutoPartition(messy, low, high, ascending);
      Quick<T>::recursion(messy, low, piv - 1, ascending);
      Quick<T>::recursion(messy, piv + 1, high, ascending);
    }
  }

  template <typename T>
  void Quick<T>::solve(std::vector<T> *messy, bool ascending) {
    if constexpr (CheckType::isNumber<T>()) {
      Quick<T>::recursion(messy, 0, messy->size() - 1, ascending);
    }
  }

  template <typename T>
  std::vector<T> Quick<T>::solve(std::vector<T> messy, bool ascending) {
    solve(&messy, ascending);
    return messy;
  }
}}}

#endif // __ALGORITHMS__SORTERS__QUICK_SORT_CPP__