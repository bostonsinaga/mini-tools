#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_SORT_CPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_SORT_CPP__

#include "../../utils/vec-tools.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {
  using namespace CheckType;

  template <typename T, typename U>
  void Merge<T, U>::merge(
    std::vector<T> &messy,
    std::vector<U> *attached,
    CR_INT left,
    CR_INT mid,
    CR_INT right,
    bool &ascending
  ) {
    int subSize[2] = {mid - left + 1, right - mid};

    std::vector<T> subVec_messy[2] = {
      utils::VecTools<T>::cutInterval(
        messy, left, left + subSize[0] - 1, true
      ),
      utils::VecTools<T>::cutInterval(
        messy, left + subSize[0], left + mid + subSize[1], true
      )
    };

    std::vector<T> subVec_attached[2];

    if constexpr (notNullptr<U>()) {
      if (attached) {
        subVec_attached[0] = utils::VecTools<T>::cutInterval(
          *attached, left, left + subSize[0] - 1, true
        );

        subVec_attached[1] = utils::VecTools<T>::cutInterval(
          *attached, left + subSize[0], left + mid + subSize[1], true
        );
      }
    }

    int subVecDex[2] = {0, 0},
      mergedVecDex = left;

    while (subVecDex[0] < subSize[0] &&
      subVecDex[1] < subSize[1]
    ) {
      if ((ascending && subVec_messy[0][subVecDex[0]]
        <= subVec_messy[1][subVecDex[1]]) ||
        (!ascending && subVec_messy[0][subVecDex[0]]
        >= subVec_messy[1][subVecDex[1]])
      ) {
        messy[mergedVecDex] = subVec_messy[0][subVecDex[0]];

        if constexpr (notNullptr<U>()) {
          if (attached) attached->at(mergedVecDex) = subVec_attached[0][subVecDex[0]];
        }

        subVecDex[0]++;
      }
      else {
        messy[mergedVecDex] = subVec_messy[1][subVecDex[1]];

        if constexpr (notNullptr<U>()) {
          if (attached) attached->at(mergedVecDex) = subVec_attached[1][subVecDex[1]];
        }

        subVecDex[1]++;
      }
      mergedVecDex++;
    }

    for (int i = 0; i < 2; i++) {
      while (subVecDex[i] < subSize[i]) {
        messy[mergedVecDex] = subVec_messy[i][subVecDex[i]];

        if constexpr (notNullptr<U>()) {
          if (attached) attached->at(mergedVecDex) = subVec_attached[i][subVecDex[i]];
        }

        subVecDex[i]++;
        mergedVecDex++;
      }
    }
  }

  template <typename T, typename U>
  void Merge<T, U>::partition(
    std::vector<T> &messy,
    std::vector<U> *attached,
    CR_INT begin,
    CR_INT end,
    bool &ascending
  ) {
    if constexpr (isNumber<T>()) {
      if (begin >= end) return;
      int mid = begin + (end - begin) / 2;

      Merge<T, U>::partition(messy, attached, begin, mid, ascending);
      Merge<T, U>::partition(messy, attached, mid + 1, end, ascending);
      Merge<T, U>::merge(messy, attached, begin, mid, end, ascending);
    }
  }

  template <typename T, typename U>
  void Merge<T, U>::solve(
    std::vector<T> &messy,
    std::vector<U> &attached,
    bool ascending
  ) {
    Merge<T, U>::partition(messy, &attached, 0, messy.size() - 1, ascending);
  }

  template <typename T, typename U>
  void Merge<T, U>::solve(
    std::vector<T> &messy,
    bool ascending
  ) {
    Merge<T, U>::partition(messy, nullptr, 0, messy.size() - 1, ascending);
  }
}}}

#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_SORT_CPP__