#ifndef __MINI_TOOLS__SORTERS__INSERTION_TPP__
#define __MINI_TOOLS__SORTERS__INSERTION_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Insertion<T, U>::process(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_ORDER_ENUM order,
    CR_INT start, CR_INT end
  ) {
    T key_messy, key_attached;

    for (int i = start + 1; i <= end; i++) {
      int j = i - 1;
      key_messy = messy[i];

      if constexpr (inspector::notNullptr<U>()) {
        key_attached = attached->at(i);
      }

      while (j >= start && (
        (order && messy[j] > key_messy) ||
        (!order && messy[j] < key_messy)
      )) {
        messy[j + 1] = messy[j];

        if constexpr (inspector::notNullptr<U>()) {
          attached->at(j + 1) = attached->at(j);
        }

        j--;
      }

      messy[j + 1] = key_messy;

      if constexpr (inspector::notNullptr<U>()) {
        attached->at(j + 1) = key_attached;
      }
    }
  }
  
  template <NUMBER T, typename U>
  void Insertion<T, U>::solve(
    VEC<T> &messy,
    VEC<U> &attached,
    CR_ORDER_ENUM order
  ) {
    VEC<U> *attached_p = nullptr;

    if (attached.size() >= messy.size()) {
      attached_p = &attached;
    }

    Insertion<T, U>::process(
      messy, &attached, order, 0, messy.size() - 1
    );
  }

  template <NUMBER T, typename U>
  void Insertion<T, U>::solve(
    VEC<T> &messy,
    CR_ORDER_ENUM order
  ) {
    Insertion<T, U>::solve(
      messy, nullptr, order, 0, messy.size() - 1
    );
  }
}}}

#endif // __MINI_TOOLS__SORTERS__INSERTION_TPP__