#ifndef __ALGORITHMS__SORTERS__BUBBLE_SORT_CPP__
#define __ALGORITHMS__SORTERS__BUBBLE_SORT_CPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <typename T>
  void Bubble<T>::solve(std::vector<T> *messy, bool ascending) {
    if constexpr (CheckType::isNumber<T>()) {
      bool stop = false;

      while (!stop) {
        stop = true;
        int i = 0;

        for (int j = 1; j < messy->size(); j++) {

          if ((ascending && messy->at(j) < messy->at(i)) ||
            (!ascending && messy->at(j) > messy->at(i))
          ) {
            stop = false;
            std::swap(messy->at(j), messy->at(i));
          }

          i = j;
        }

        if (stop) break;
      }
    }
  }

  template <typename T>
  std::vector<T> Bubble<T>::solve(std::vector<T> messy, bool ascending) {
    Bubble<T>::solve(&messy, ascending);
    return messy;
  }
}}}

#endif // __ALGORITHMS__SORTERS__BUBBLE_SORT_CPP__