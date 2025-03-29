#ifndef __MINI_TOOLS__SORTERS__SELECTION_TPP__
#define __MINI_TOOLS__SORTERS__SELECTION_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Selection<T, U>::process(
    std::vector<T> &messy,
    std::vector<U> *attached,
    CR_ORDER_ENUM order
  ) {
    int i, j, least; 

    for (i = 0; i < messy.size() - 1; i++) {
      least = i; 

      for (j = i + 1; j < messy.size(); j++) {
        if ((order && messy[j] < messy[least]) ||
          (!order && messy[j] > messy[least])
        ) { least = j; }
      }

      std::swap(messy[least], messy[i]);

      if constexpr (notNullptr<U>()) {
        if (attached) std::swap(
          attached->at(least), attached->at(i)
        );
      }
    }
  }

	template <NUMBER T, typename U>
  void Selection<T, U>::solve(
    std::vector<T> &messy,
    std::vector<U> &attached,
    CR_ORDER_ENUM order
  ) {
    std::vector<U> *attached_p = nullptr;

    if (attached.size() >= messy.size()) {
      attached_p = &attached;
    }

    Selection<T, U>::process(messy, attached_p, order);
  }

  template <NUMBER T, typename U>
  void Selection<T, U>::solve(
    std::vector<T> &messy,
    CR_ORDER_ENUM order
  ) {
    Selection<T, U>::process(messy, nullptr, order);
  }
}}}

#endif // __MINI_TOOLS__SORTERS__SELECTION_TPP__