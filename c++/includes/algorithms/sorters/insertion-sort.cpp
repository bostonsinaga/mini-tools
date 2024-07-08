#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_CPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_CPP__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  void Insertion<T>::solve(
    std::vector<T> *messy,
    bool ascending
  ) {
    int i, key, j;

    for (i = 1; i < messy->size(); i++) {

      key = messy->at(i);
      j = i - 1;

      while (j >= 0 && messy->at(j) > key) {
        messy->at(j + 1) = messy->at(j);
        j = j - 1;
      }

      messy->at(j + 1) = key;
    }
  }

  std::vector<T> Insertion<T>::solve(
    std::vector<T> messy,
    bool ascending
  ) {
    Insertion<T>::solve(&messy, ascending);
    return messy;
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_CPP__