#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_CPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_CPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {
  using namespace CheckType;

  template <typename T, typename U>
  void Insertion<T, U>::process(
    std::vector<T> &messy,
    std::vector<U> *attached,
    CR_BOL ascending,
    CR_INT start, CR_INT end
  ) {
    if constexpr (isNumber<T>()) {
      T key_messy, key_attached;

      for (int i = start + 1; i <= end; i++) {
        int j = i - 1;
        key_messy = messy[i];

        if constexpr (notNullptr<U>()) {
          key_attached = attached->at(i);
        }

        while (j >= start && (
          (ascending && messy[j] > key_messy) ||
          (!ascending && messy[j] < key_messy)
        )) {
          messy[j + 1] = messy[j];

          if constexpr (notNullptr<U>()) {
            attached->at(j + 1) = attached->at(j);
          }

          j--;
        }

        messy[j + 1] = key_messy;

        if constexpr (notNullptr<U>()) {
          attached->at(j + 1) = key_attached;
        }
      }
    }
  }
  
  template <typename T, typename U>
  void Insertion<T, U>::solve(
    std::vector<T> &messy,
    std::vector<U> &attached,
    CR_BOL ascending
  ) {
    std::vector<U> *attached_p = nullptr;
    if (attached.size() >= messy.size()) attached_p = &attached;
    Insertion<T, U>::process(messy, attached_p, ascending, 0, messy.size());
  }

  template <typename T, typename U>
  void Insertion<T, U>::solve(
    std::vector<T> &messy,
    CR_BOL ascending
  ) {
    Insertion<T, U>::solve(messy, nullptr, ascending, 0, messy.size());
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_CPP__