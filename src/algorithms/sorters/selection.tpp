#ifndef __MINI_TOOLS__SORTERS__SELECTION_TPP__
#define __MINI_TOOLS__SORTERS__SELECTION_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Selection<T, U>::process(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    int i, j, least; 

    for (i = 0; i < messy.size() - 1; i++) {
      least = i; 

      for (j = i + 1; j < messy.size(); j++) {
        if ((order && messy[j].first < messy[least].first) ||
          (!order && messy[j].first > messy[least].first)
        ) { least = j; }
      }

      std::swap(messy[least], messy[i]);
    }
  }

  template <NUMBER T, typename U>
  void Selection<T, U>::solve(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    Selection<T, U>::process(messy, order);
  }
}}}

#endif // __MINI_TOOLS__SORTERS__SELECTION_TPP__