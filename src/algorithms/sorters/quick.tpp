#ifndef __MINI_TOOLS__SORTERS__QUICK_TPP__
#define __MINI_TOOLS__SORTERS__QUICK_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  int Quick<T, U, SCHEME>::lomutoPartition(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order,
    CR_INT left,
    CR_INT right
  ) {
    int i = left - 1;

    for (int j = left; j < right; j++) {

      if ((order == ORDER_ASCENDING &&
        messy[j].first <= messy[right].first)
      ||
        (order == ORDER_DESCENDING &&
        messy[j].first >= messy[right].first)
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
    CR_ORDER_ENUM order,
    CR_INT left,
    CR_INT right
  ) {
    int i = left - 1, j = right + 1;
    const int mid = (left + right) / 2;

    while (true) {
      if (order == ORDER_ASCENDING) {
        do { i++; } while (messy[i].first < messy[mid].first);
        do { j--; } while (messy[j].first > messy[mid].first);
      }
      else {
        do { i++; } while (messy[i].first > messy[mid].first);
        do { j--; } while (messy[j].first < messy[mid].first);
      }

      if (i >= j) return j;
      std::swap(messy[i], messy[j]);
    }
  }

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  int Quick<T, U, SCHEME>::randomPartition(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order,
    CR_INT left,
    CR_INT right
  ) {
    std::srand(std::time(NULL));
    int random = left + std::rand() % (right - left);
    std::swap(messy[random], messy[right]);

    if constexpr (SCHEME == QUICK_LOMUTO) {
      return Quick<T, U, SCHEME>::lomutoPartition(
        messy, order, left, right
      );
    }
    else return Quick<T, U, SCHEME>::hoarePartition(
      messy, order, left, right
    );
  }

  template <inspector::NUMBER T, typename U, QUICK_SCHEME_ENUM SCHEME>
  void Quick<T, U, SCHEME>::recursion(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order,
    CR_INT left,
    CR_INT right
  ) {
    if (left < right) {
      if (right - left <= 100) {
        Insertion<T, U>::process(messy, order, left, right);
      }
      else {
        int pix = Quick<T, U, SCHEME>::randomPartition(
          messy, order, left, right
        );

        Quick<T, U, SCHEME>::recursion(
          messy, order, left, pix - 1
        );

        Quick<T, U, SCHEME>::recursion(
          messy, order, pix + 1, right
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
      messy, order, 0, messy.size() - 1
    );
  }
}}}

#endif // __MINI_TOOLS__SORTERS__QUICK_TPP__