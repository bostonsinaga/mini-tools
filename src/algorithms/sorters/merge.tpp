#ifndef __MINI_TOOLS__SORTERS__MERGE_TPP__
#define __MINI_TOOLS__SORTERS__MERGE_TPP__

#include "utils/vec-tools.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <NUMBER T, typename U>
  void Merge<T, U>::merge(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT left,
    CR_INT mid,
    CR_INT right,
    CR_ORDER_ENUM order
  ) {
    int subSize[2] = {mid - left + 1, right - mid};

    VEC<T> subVec_messy[2] = {
      utils::VecTools<T>::cutInterval(
        messy, left, left + subSize[0] - 1, true
      ),
      utils::VecTools<T>::cutInterval(
        messy, left + subSize[0], left + mid + subSize[1], true
      )
    };

    VEC<T> subVec_attached[2];

    if constexpr (inspector::notNullptr<U>()) {
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
      if ((order && subVec_messy[0][subVecDex[0]]
        <= subVec_messy[1][subVecDex[1]]) ||
        (!order && subVec_messy[0][subVecDex[0]]
        >= subVec_messy[1][subVecDex[1]])
      ) {
        messy[mergedVecDex] = subVec_messy[0][subVecDex[0]];

        if constexpr (inspector::notNullptr<U>()) {
          if (attached) attached->at(mergedVecDex) = subVec_attached[0][subVecDex[0]];
        }

        subVecDex[0]++;
      }
      else {
        messy[mergedVecDex] = subVec_messy[1][subVecDex[1]];

        if constexpr (inspector::notNullptr<U>()) {
          if (attached) attached->at(mergedVecDex) = subVec_attached[1][subVecDex[1]];
        }

        subVecDex[1]++;
      }

      mergedVecDex++;
    }

    for (int i = 0; i < 2; i++) {

      while (subVecDex[i] < subSize[i]) {
        messy[mergedVecDex] = subVec_messy[i][subVecDex[i]];

        if constexpr (inspector::notNullptr<U>()) {
          if (attached) attached->at(mergedVecDex) = subVec_attached[i][subVecDex[i]];
        }

        subVecDex[i]++;
        mergedVecDex++;
      }
    }
  }

  template <NUMBER T, typename U>
  void Merge<T, U>::partition(
    VEC<T> &messy,
    VEC<U> *attached,
    CR_INT begin,
    CR_INT end,
    CR_ORDER_ENUM order
  ) {
    if (begin >= end) return;
    int mid = begin + (end - begin) / 2;

    Merge<T, U>::partition(messy, attached, begin, mid, order);
    Merge<T, U>::partition(messy, attached, mid + 1, end, order);
    Merge<T, U>::merge(messy, attached, begin, mid, end, order);
  }

  template <NUMBER T, typename U>
  void Merge<T, U>::solve(
    VEC<T> &messy,
    VEC<U> &attached,
    CR_ORDER_ENUM order
  ) {
    VEC<U> *attached_p = nullptr;

    if (attached.size() >= messy.size()) {
      attached_p = &attached;
    }

    Merge<T, U>::partition(
      messy, attached_p, 0, messy.size() - 1, order
    );
  }

  template <NUMBER T, typename U>
  void Merge<T, U>::solve(
    VEC<T> &messy,
    CR_ORDER_ENUM order
  ) {
    Merge<T, U>::partition(
      messy, nullptr, 0, messy.size() - 1, order
    );
  }
}}}

#endif // __MINI_TOOLS__SORTERS__MERGE_TPP__