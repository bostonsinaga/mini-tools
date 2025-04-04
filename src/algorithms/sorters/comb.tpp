#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_TPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, typename U>
  void Comb<T, U>::process(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    int gap = messy.size();
    bool swapped = true;

    while (gap != 1 || swapped) {
      /**
       * Starts with a large value
       * and shrinks by a factor of 1.3
       */
      gap = (gap * 10) / 13;

      if (gap < 1) gap = 1;
      swapped = false;

      for (int i = 0; i < messy.size() - gap; i++) {

        if ((order == ORDER_ASCENDING &&
          messy[i].first > messy[i + gap].first)
        ||
          (order == ORDER_DESCENDING &&
          messy[i].first < messy[i + gap].first)
        ) {
          swapped = true;
          std::swap(messy[i], messy[i + gap]);
        }
      }
    }
  }

  template <inspector::NUMBER T, typename U>
  void Comb<T, U>::solve(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    Comb<T, U>::process(messy, nullptr, order);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_TPP__