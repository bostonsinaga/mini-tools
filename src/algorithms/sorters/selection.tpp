#ifndef __MINI_TOOLS__SORTERS__SELECTION_TPP__
#define __MINI_TOOLS__SORTERS__SELECTION_TPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  using namespace CheckType;

  template <typename T, typename U>
  void Selection<T, U>::process(
    std::vector<T> &messy,
    std::vector<U> *attached,
    bool &ascending
  ) {
    if constexpr (isNumber<T>()) {
      int i, j, least; 

      for (i = 0; i < messy.size() - 1; i++) {
        least = i; 

        for (j = i + 1; j < messy.size(); j++) {
          if ((ascending && messy[j] < messy[least]) ||
            (!ascending && messy[j] > messy[least])
          ) { least = j; }
        }

        std::swap(messy[least], messy[i]);

        if constexpr (notNullptr<U>()) {
          if (attached) std::swap(attached->at(least), attached->at(i));
        }
      }
    }
  }

	template <typename T, typename U>
  void Selection<T, U>::solve(
    std::vector<T> &messy,
    std::vector<U> &attached,
    bool ascending
  ) {
    std::vector<U> *attached_p = nullptr;
    if (attached.size() >= messy.size()) attached_p = &attached;
    Selection<T, U>::process(messy, attached_p, ascending);
  }

  template <typename T, typename U>
  void Selection<T, U>::solve(
    std::vector<T> &messy,
    bool ascending
  ) {
    Selection<T, U>::process(messy, nullptr, ascending);
  }
}}}

#endif // __MINI_TOOLS__SORTERS__SELECTION_TPP__