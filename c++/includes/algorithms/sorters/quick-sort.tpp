#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_CPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_CPP__

#include <ctime>

namespace mini_tools {
namespace algorithms {
namespace sorters {
  using namespace CheckType;

  template <typename T, typename U>
  int Quick<T, U>::lomutoPartition(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    bool &ascending
  ) {
    T pivot = messy[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
      if ((ascending && messy[j] <= pivot) ||
        (!ascending && messy[j] >= pivot)
      ) {
        i++;
        std::swap(messy[i], messy[j]);

        if constexpr (notNullptr<U>()) {
          if (attached) std::swap(attached->at(i), attached->at(j));
        }
      }
    }

    std::swap(messy[i + 1], messy[right]);

    if constexpr (notNullptr<U>()) {
      if (attached) std::swap(attached->at(i + 1), attached->at(right));
    }

    return i + 1;
  }

  template <typename T, typename U>
  int Quick<T, U>::hoarePartition(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    bool &ascending
  ) {
    int i = left - 1, j = right + 1;
    int pivot = messy[(left + right) / 2];

    while (true) {
      if (ascending) {
        do { i++; } while (messy[i] < pivot);
        do { j--; } while (messy[j] > pivot);
      }
      else {
        do { i++; } while (messy[i] > pivot);
        do { j--; } while (messy[j] < pivot);
      }

      if (i >= j) return j;
      std::swap(messy[i], messy[j]);

      if constexpr (notNullptr<U>()) {
        if (attached) std::swap(attached->at(i), attached->at(j));
      }
    }
  }

  template <typename T, typename U>
  int Quick<T, U>::randomPartition(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    bool &ascending,
    int &scheme
  ) {
    std::srand(std::time(NULL));
    int random = left + std::rand() % (right - left);
    std::swap(messy[random], messy[right]);

    if constexpr (notNullptr<U>()) {
      if (attached) std::swap(attached->at(random), attached->at(right));
    }

    if (scheme == LOMUTO) {
      return Quick<T, U>::lomutoPartition(messy, attached, left, right, ascending);
    }
    else return Quick<T, U>::hoarePartition(messy, attached, left, right, ascending);
  }

  template <typename T, typename U>
  void Quick<T, U>::recursion(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    bool &ascending,
    int &scheme
  ) {
    if constexpr (isNumber<T>()) {
      if (left < right) {
        if (right - left <= 100) {
          Insertion<T, U>::process(messy, attached, ascending, left, right);
        }
        else {
          int piv = randomPartition(messy, attached, left, right, ascending, scheme);
          Quick<T, U>::recursion(messy, attached, left, piv - 1, ascending, scheme);
          Quick<T, U>::recursion(messy, attached, piv + 1, right, ascending, scheme);
        }
      }
    }
  }

  template <typename T, typename U>
  void Quick<T, U>::solve(
    VEC<T> &messy,
    VEC<U> &attached,
    bool ascending,
    int scheme
  ) {
    VEC<U> *attached_p = nullptr;
    if (attached.size() >= messy.size()) attached_p = &attached;
    Quick<T, U>::recursion(messy, attached_p, 0, messy.size() - 1, ascending, scheme);
  }

  template <typename T, typename U>
  void Quick<T, U>::solve(
    VEC<T> &messy,
    bool ascending,
    int scheme
  ) {
    Quick<T, U>::recursion(messy, nullptr, 0, messy.size() - 1, ascending, scheme);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_CPP__