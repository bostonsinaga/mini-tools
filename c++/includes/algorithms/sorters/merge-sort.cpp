#ifndef __ALGORITHMS__SORTERS__MERGE_SORT_CPP__
#define __ALGORITHMS__SORTERS__MERGE_SORT_CPP__

#include "../../utils/vec-tools.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <typename T>
  void Merge<T>::merge(std::vector<T> *messy, CR_INT left, CR_INT mid, CR_INT right) {

    int subSize[2] = {mid - left + 1, right - mid};

    std::vector<T> subVec[2] = {
      utils::VecTools<T>::cutInterval(
        *messy, left, left + subSize[0] - 1, true
      ),
      utils::VecTools<T>::cutInterval(
        *messy, left + subSize[0], left + mid + subSize[1], true
      )
    };

    int subVecDex[2] = {0, 0},
        mergedVecDex = left;

    while (subVecDex[0] < subSize[0] &&
      subVecDex[1] < subSize[1]
    ) {
      if (subVec[0][subVecDex[0]] <= subVec[1][subVecDex[1]]) {
        messy->at(mergedVecDex) = subVec[0][subVecDex[0]];
        subVecDex[0]++;
      }
      else {
        messy->at(mergedVecDex) = subVec[1][subVecDex[1]];
        subVecDex[1]++;
      }
      mergedVecDex++;
    }

    for (int i = 0; i < 2; i++) {
      while (subVecDex[i] < subSize[i]) {
        messy->at(mergedVecDex) = subVec[i][subVecDex[i]];
        subVecDex[i]++;
        mergedVecDex++;
      }
    }
  }

  template <typename T>
  void Merge<T>::partition(std::vector<T> *messy, CR_INT begin, CR_INT end) {
    if (begin >= end) return;
    int mid = begin + (end - begin) / 2;

    Merge<T>::partition(messy, begin, mid);
    Merge<T>::partition(messy, mid + 1, end);
    Merge<T>::merge(messy, begin, mid, end);
  }

  template <typename T>
  void Merge<T>::solve(std::vector<T> *messy) {
    if constexpr (CheckType::isNumber<T>()) {
      Merge<T>::partition(messy, 0, messy->size() - 1);
    }
  }

  template <typename T>
  std::vector<T> Merge<T>::solve(std::vector<T> messy) {
    Merge<T>::solve(&messy);
    return messy;
  }
}}}

#endif // __ALGORITHMS__SORTERS__MERGE_SORT_CPP__