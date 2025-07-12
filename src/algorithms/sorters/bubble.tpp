#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, typename U>
  void Bubble<T, U>::process(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    for (int i = 0; i < messy.size() - 1; i++) {
      for (int j = 0; j < messy.size() - i - 1; j++) {

        if ((order == ORDER_ASCENDING &&
          messy[j].first > messy[j + 1].first)
        ||
          (order == ORDER_DESCENDING &&
          messy[j].first < messy[j + 1].first)
        ) {
          std::swap(messy[j], messy[j + 1]);
        }
      }
    }
  }

  template <inspector::NUMBER T, typename U>
  void Bubble<T, U>::solve(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    Bubble<T, U>::process(messy, order);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__