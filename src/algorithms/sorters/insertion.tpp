#ifndef __MINI_TOOLS__SORTERS__INSERTION_TPP__
#define __MINI_TOOLS__SORTERS__INSERTION_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Insertion<T, U>::process(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order,
    CR_INT start,
    CR_INT end
  ) {
    PAIR2<T, U> key;

    for (int i = start + 1; i <= end; i++) {
      int j = i - 1;
      key = messy[i];

      while (j >= start && (
        (order && messy[j].first > key) ||
        (!order && messy[j].first < key)
      )) {
        messy[j + 1] = messy[j];
        j--;
      }

      messy[j + 1] = key;
    }
  }

  template <NUMBER T, typename U>
  void Insertion<T, U>::solve(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    Insertion<T, U>::solve(
      messy, nullptr, order, 0, messy.size() - 1
    );
  }
}}}

#endif // __MINI_TOOLS__SORTERS__INSERTION_TPP__