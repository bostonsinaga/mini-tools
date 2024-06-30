#ifndef __ALGORITHMS__SORTERS__SELECTION_SORT_CPP__
#define __ALGORITHMS__SORTERS__SELECTION_SORT_CPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

	template <typename T>
  void Selection<T>::solve(std::vector<T> *messy) {
    if constexpr (CheckType::isNumber<T>()) {
      int i, j, least; 

      for (i = 0; i < messy->size() - 1; i++) {
        least = i; 

        for (j = i + 1; j < messy->size(); j++) {
          if (messy->at(j) < messy->at(least)) least = j;
        }

        std::swap(messy->at(least), messy->at(i));
      }
    }
  }

  template <typename T>
  std::vector<T> Selection<T>::solve(std::vector<T> messy) {
    Selection<T>::solve(&messy);
    return messy;
  }
}}}

#endif // __ALGORITHMS__SORTERS__SELECTION_SORT_CPP__