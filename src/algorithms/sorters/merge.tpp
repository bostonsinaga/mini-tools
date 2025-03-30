#ifndef __MINI_TOOLS__SORTERS__MERGE_TPP__
#define __MINI_TOOLS__SORTERS__MERGE_TPP__

#include "utils/vec-tools.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Merge<T, U>::merge(
    VEC_PAIR2<T, U> &messy,
    CR_INT left,
    CR_INT mid,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    int subSize[2] = {mid - left + 1, right - mid};

    VEC_PAIR2<T, U> subVec[2] = {
      utils::VecTools<T>::cutInterval(
        messy, left, left + subSize[0] - 1, true
      ),
      utils::VecTools<T>::cutInterval(
        messy, left + subSize[0], left + mid + subSize[1], true
      )
    };

    int subVecDex[2] = {0, 0},
      mergedVecDex = left;

    while (subVecDex[0] < subSize[0] &&
      subVecDex[1] < subSize[1]
    ) {
      if ((order == ORDER_ASCENDING &&
        subVec[0][subVecDex[0]].first <= subVec[1][subVecDex[1]].first)
      ||
        (order == ORDER_DESCENDING &&
        subVec[0][subVecDex[0]].first >= subVec[1][subVecDex[1]].first)
      ) {
        messy[mergedVecDex] = subVec[0][subVecDex[0]];
        subVecDex[0]++;
      }
      else {
        messy[mergedVecDex] = subVec[1][subVecDex[1]];
        subVecDex[1]++;
      }

      mergedVecDex++;
    }

    for (int i = 0; i < 2; i++) {

      while (subVecDex[i] < subSize[i]) {
        messy[mergedVecDex] = subVec[i][subVecDex[i]];
        subVecDex[i]++;
        mergedVecDex++;
      }
    }
  }

  template <NUMBER T, typename U>
  void Merge<T, U>::partition(
    VEC_PAIR2<T, U> &messy,
    CR_INT begin,
    CR_INT end,
    CR_ORDER_ENUM order
  ) {
    if (begin >= end) return;
    int mid = begin + (end - begin) / 2;

    Merge<T, U>::partition(messy, begin, mid, order);
    Merge<T, U>::partition(messy, mid + 1, end, order);
    Merge<T, U>::merge(messy, begin, mid, end, order);
  }

  template <NUMBER T, typename U>
  void Merge<T, U>::solve(
    VEC_PAIR2<T, U> &messy,
    CR_ORDER_ENUM order
  ) {
    Merge<T, U>::partition(
      messy, 0, messy.size() - 1, order
    );
  }
}}}

#endif // __MINI_TOOLS__SORTERS__MERGE_TPP__