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
    bool &ascending
  ) {
    if constexpr (isNumber<T>()) {
      int i, j;
      T key_messy, key_attached;

      for (i = 0; i < messy.size(); i++) {
        j = i - 1;
        key_messy = messy[i];

        if constexpr (notNullptr<U>()) {
          key_attached = attached->at(i);
        }

        while (j >= 0 && (
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
    bool ascending
  ) {
    Insertion<T, U>::process(messy, &attached, ascending);
  }

  template <typename T, typename U>
  void Insertion<T, U>::solve(
    std::vector<T> &messy,
    bool ascending
  ) {
    Insertion<T, U>::process(messy, nullptr, ascending);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_CPP__