#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_SORT_CPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_SORT_CPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {
  using namespace CheckType;

  template <typename T, typename U>
  void Comb<T, U>::process(
    std::vector<T> &messy,
    std::vector<U> *attached,
    bool &ascending
  ) {
    if constexpr (isNumber<T>()) {
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
          if ((ascending && messy[i] > messy[i + gap]) ||
            (!ascending && messy[i] < messy[i + gap])
          ) {
            std::swap(messy[i], messy[i + gap]);
            swapped = true;

            if constexpr (notNullptr<U>()) {
              if (attached) std::swap(attached->at(i), attached->at(i + gap));
            }
          }
        }
      }
    }
  }

  template <typename T, typename U>
  void Comb<T, U>::solve(
    std::vector<T> &messy,
    std::vector<U> &attached,
    bool ascending
  ) {
    std::vector<U> *attached_p = nullptr;
    if (attached.size() >= messy.size()) attached_p = &attached;
    Comb<T, U>::process(messy, attached_p, ascending);
  }

  template <typename T, typename U>
  void Comb<T, U>::solve(
    std::vector<T> &messy,
    bool ascending
  ) {
    Comb<T, U>::process(messy, nullptr, ascending);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_SORT_CPP__