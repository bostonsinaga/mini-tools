#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  using namespace CheckType;

  template <typename T, typename U>
  void Bubble<T, U>::process(
    VEC<T> &messy,
    VEC<U> *attached,
    bool &ascending
  ) {
    if constexpr (isNumber<T>()) {
      for (int i = 0; i < messy.size() - 1; i++) {
        for (int j = 0; j < messy.size() - i - 1; j++) {
          if ((ascending && messy[j] > messy[j + 1]) ||
            (!ascending && messy[j] < messy[j + 1])
          ) {
            std::swap(messy[j], messy[j + 1]);

            if constexpr (notNullptr<U>()) {
              if (attached) std::swap(attached->at(j), attached->at(j + 1));
            }
          }
        }
      }
    }
  }

  template <typename T, typename U>
  void Bubble<T, U>::solve(
    VEC<T> &messy,
    VEC<U> &attached,
    bool ascending
  ) {
    VEC<U> *attached_p = nullptr;
    if (attached.size() >= messy.size()) attached_p = &attached;
    Bubble<T, U>::process(messy, attached_p, ascending);
  }

  template <typename T, typename U>
  void Bubble<T, U>::solve(
    VEC<T> &messy,
    bool ascending
  ) {
    Bubble<T, U>::process(messy, nullptr, ascending);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_TPP__