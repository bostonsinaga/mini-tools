#ifndef __ALGORITHMS__SORTERS__QUICK_SORT_CPP__
#define __ALGORITHMS__SORTERS__QUICK_SORT_CPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <typename T>
  int Quick<T>::partition(std::vector<T> *messy, CR_INT left, CR_INT right) {
    int i = left - 1;

    for (int j = left; j < right; j++) {
      if (messy->at(j) < messy->at(right)) {
        i++;
        std::swap(messy->at(i), messy->at(j));
      }
    }

    std::swap(messy->at(i+1), messy->at(right));
    return i+1;
  }

  template <typename T>
  void Quick<T>::recursion(std::vector<T> *messy, CR_INT left, CR_INT right) {
    if (left < right) {
      int piv = partition(messy, left, right);
      Quick<T>::recursion(messy, left, piv - 1);
      Quick<T>::recursion(messy, piv + 1, right);
    }
  }

  template <typename T>
  void Quick<T>::solve(std::vector<T> *messy) {
    if constexpr (CheckType::isNumber<T>()) {
      Quick<T>::recursion(messy, 0, messy->size() - 1);
    }
  }

  template <typename T>
  std::vector<T> Quick<T>::solve(std::vector<T> messy) {
    solve(&messy);
    return messy;
  }
}}}

#endif // __ALGORITHMS__SORTERS__QUICK_SORT_CPP__