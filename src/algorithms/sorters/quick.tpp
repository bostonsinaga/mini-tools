#ifndef __MINI_TOOLS__SORTERS__QUICK_TPP__
#define __MINI_TOOLS__SORTERS__QUICK_TPP__

#include <ctime>

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, typename U>
  int Quick<T, U>::lomutoPartition(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    T pivot = messy[right];
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
      if ((order && messy[j] <= pivot) ||
        (!order && messy[j] >= pivot)
      ) {
        i++;
        swap<T, U>(messy, attached, i, j);
      }
    }

    swap<T, U>(messy, attached, i + 1, right);
    return i + 1;
  }

  template <inspector::NUMBER T, typename U>
  int Quick<T, U>::hoarePartition(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    int i = left - 1, j = right + 1;
    int pivot = messy[(left + right) / 2];

    while (true) {
      if (order) {
        do { i++; } while (messy[i] < pivot);
        do { j--; } while (messy[j] > pivot);
      }
      else {
        do { i++; } while (messy[i] > pivot);
        do { j--; } while (messy[j] < pivot);
      }

      if (i >= j) return j;
      swap<T, U>(messy, attached, i, j);
    }
  }

  template <inspector::NUMBER T, typename U>
  int Quick<T, U>::randomPartition(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order,
    CR_SCHEME scheme
  ) {
    std::srand(std::time(NULL));
    int random = left + std::rand() % (right - left);
    swap<T, U>(messy, attached, random, right);

    if (scheme == LOMUTO) {
      return Quick<T, U>::lomutoPartition(
        messy, attached, left, right, order
      );
    }

    return Quick<T, U>::hoarePartition(
      messy, attached, left, right, order
    );
  }

  template <inspector::NUMBER T, typename U>
  void Quick<T, U>::recursion(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order,
    CR_SCHEME scheme
  ) {
    if (left < right) {
      if (right - left <= 100) {
        Insertion<T, U>::process(
          messy, attached, order, left, right
        );
      }
      else {
        int piv = randomPartition(
          messy, attached, left, right, order, scheme
        );

        Quick<T, U>::recursion(
          messy, attached, left, piv - 1, order, scheme
        );

        Quick<T, U>::recursion(
          messy, attached, piv + 1, right, order, scheme
        );
      }
    }
  }

  template <inspector::NUMBER T, typename U>
  void Quick<T, U>::solve(
    VEC<T> &messy,
    VEC<U> &attached,
    CR_ORDER_ENUM order,
    CR_SCHEME scheme
  ) {
    VEC<U> *attached_p = nullptr;

    if (attached.size() >= messy.size()) {
      attached_p = &attached;
    }

    Quick<T, U>::recursion(
      messy, attached_p, 0, messy.size() - 1, order, scheme
    );
  }

  template <inspector::NUMBER T, typename U>
  void Quick<T, U>::solve(
    VEC<T> &messy,
    CR_ORDER_ENUM order,
    CR_SCHEME scheme
  ) {
    Quick<T, U>::recursion(
      messy, nullptr, 0, messy.size() - 1, order, scheme
    );
  }
}}}

#endif // __MINI_TOOLS__SORTERS__QUICK_TPP__