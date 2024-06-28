#include "../../types.h"
#include "../../utils/vec-tools.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  class Merge {
  private:
    static void merge(
      VEC_INT &messy, int left, int mid, int right
    ) {
      int subSize[2] = {mid - left + 1, right - mid};

      VEC_INT subVec[2] = {
        utils::VecTools<int>::cutInterval(
          messy, left, left + subSize[0] - 1, true
        ),
        utils::VecTools<int>::cutInterval(
          messy, left + subSize[0], left + mid + subSize[1], true
        )
      };

      int subVecDex[2] = {0, 0},
          mergedVecDex = left;

      while (subVecDex[0] < subSize[0] &&
        subVecDex[1] < subSize[1]
      ) {
        if (subVec[0][subVecDex[0]] <= subVec[1][subVecDex[1]]) {
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

    static void partition(VEC_INT &messy, int begin, int end) {

      if (begin >= end) return;
      int mid = begin + (end - begin) / 2;

      partition(messy, begin, mid);
      partition(messy, mid + 1, end);
      merge(messy, begin, mid, end);
    }

  public:
    static void solve(VEC_INT &messy) {
      partition(messy, 0, messy.size() - 1);
    }
  };
}}}
