#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_TPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Comb<T, U>::process(
    VEC<T> &messy,
    VEC<U> *attached,
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
        if ((order && messy[i] > messy[i + gap]) ||
          (!order && messy[i] < messy[i + gap])
        ) {
          swapped = true;
          swap<T, U>(messy, attached, i, i + gap);
        }
      }
    }
  }

  template <NUMBER T, typename U>
  void Comb<T, U>::solve(
    VEC<T> &messy,
    VEC<U> &attached,
    CR_ORDER_ENUM order
  ) {
    VEC<U> *attached_p = nullptr;

    if (attached.size() >= messy.size()) {
      ttached_p = &attached;
    }

    Comb<T, U>::process(messy, attached_p, order);
  }

  template <NUMBER T, typename U>
  void Comb<T, U>::solve(
    VEC<T> &messy,
    CR_ORDER_ENUM order
  ) {
    Comb<T, U>::process(messy, nullptr, order);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_TPP__