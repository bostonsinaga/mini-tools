#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Bubble<T, U>::process(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_ORDER_ENUM order
  ) {
    for (int i = 0; i < messy.size() - 1; i++) {
      for (int j = 0; j < messy.size() - i - 1; j++) {
        if ((order && messy[j] > messy[j + 1]) ||
          (!order && messy[j] < messy[j + 1])
        ) {
          std::swap(messy[j], messy[j + 1]);

          if constexpr (notNullptr<U>()) {
            if (attached) std::swap(
              attached->at(j), attached->at(j + 1)
            );
          }
        }
      }
    }
  }

  template <NUMBER T, typename U>
  void Bubble<T, U>::solve(
    VEC<T> &messy,
    VEC<U> &attached,
    CR_ORDER_ENUM order
  ) {
    VEC<U> *attached_p = nullptr;

    if (attached.size() >= messy.size()) {
      attached_p = &attached;
    }

    Bubble<T, U>::process(messy, attached_p, order);
  }

  template <NUMBER T, typename U>
  void Bubble<T, U>::solve(
    VEC<T> &messy,
    CR_ORDER_ENUM order
  ) {
    Bubble<T, U>::process(messy, nullptr, order);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__