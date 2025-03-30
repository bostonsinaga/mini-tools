#ifndef __MINI_TOOLS__SORTERS__QUICK_TPP__
#define __MINI_TOOLS__SORTERS__QUICK_TPP__

#include <ctime>

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  int Quick<T, U, SCHEME>::lomutoPartition(
    VEC_PAIR2<T, U> &messy,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    T pivot = messy[right].first;
    int i = left - 1;

    for (int j = left; j <= right - 1; j++) {
      if ((order && messy[j].first <= pivot) ||
        (!order && messy[j].first >= pivot)
      ) {
        i++;
        std::swap(messy[i], messy[j]);
      }
    }

    std::swap(messy[i + 1], messy[right]);
    return i + 1;
  }

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  int Quick<T, U, SCHEME>::hoarePartition(
    VEC_PAIR2<T, U> &messy,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    int i = left - 1, j = right + 1;
    int pivot = messy[(left + right) / 2].first;

    while (true) {
      if (order) {
        do { i++; } while (messy[i].first < pivot);
        do { j--; } while (messy[j].first > pivot);
      }
      else {
        do { i++; } while (messy[i].first > pivot);
        do { j--; } while (messy[j].first < pivot);
      }

      if (i >= j) return j;
      std::swap(messy[i], messy[j]);
    }
  }

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  int Quick<T, U, SCHEME>::randomPartition(
    VEC_PAIR2<T, U> &messy,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    std::srand(std::time(NULL));
    int random = left + std::rand() % (right - left);
    std::swap(messy[random], messy[right]);

    if constexpr (SCHEME == QUICK_LOMUTO) {
      return Quick<T, U, SCHEME>::lomutoPartition(
        messy, left, right, order
      );
    }
    else return Quick<T, U, SCHEME>::hoarePartition(
      messy, left, right, order
    );
  }

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  void Quick<T, U, SCHEME>::recursion(
    VEC_PAIR2<T, U> &messy,
    CR_INT left,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    if (left < right) {
      if (right - left <= 100) {
        Insertion<T, U>::process(messy, order, left, right);
      }
      else {
        int piv = Quick<T, U, SCHEME>::randomPartition(
          messy, left, right, order
        );

        Quick<T, U, SCHEME>::recursion(
          messy, left, piv - 1, order
        );

        Quick<T, U, SCHEME>::recursion(
          messy, piv + 1, right, order
        );
      }
    }
  }

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  void Quick<T, U, SCHEME>::solve(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    Quick<T, U, SCHEME>::recursion(
      messy, 0, messy.size() - 1, order
    );
  }
}}}

#endif // __MINI_TOOLS__SORTERS__QUICK_TPP__