#ifndef __ALGORITHMS__SORTERS__QUICK_SORT_H__
#define __ALGORITHMS__SORTERS__QUICK_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  class Quick {
  private:
    // 'left' and 'right' are index of 'messy'
    static int partition(
      VEC_INT &messy, CR_INT left, CR_INT right
    ) {
      int i = left - 1;

      for (int j = left; j < right; j++) {
        if (messy[j] < messy[right]) {
          i++;
          std::swap(messy[i], messy[j]);
        }
      }

      std::swap(messy[i+1], messy[right]);
      return i+1;
    }

    // 'left' and 'right' are index of 'messy'
    static void recursion(
      VEC_INT &messy, CR_INT left, CR_INT right
    ) {
      if (left < right) {
        CR_INT piv = partition(messy, left, right);
        recursion(messy, left, piv - 1);
        recursion(messy, piv + 1, right);
      }
    }

  public:
    static void solve(VEC_INT &messy) {
      recursion(messy, 0, messy.size() - 1);
    }
  };
}}}

#endif // __ALGORITHMS__SORTERS__QUICK_SORT_H__