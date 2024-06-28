#ifndef __ALGORITHMS__SORTERS__COMB_SORT_H__
#define __ALGORITHMS__SORTERS__COMB_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  class Comb {
  public:
    static void solve(VEC_INT &messy) {

      int gap = messy.size();
      bool swapped = true;
      int errCtr = 0;

      while (gap != 1 || swapped) {
        /**
         * Starts with a large value
         * and shrinks by a factor of 1.3
         */
        gap = (gap * 10) / 13;

        if (gap < 1) gap = 1;
        swapped = false;

        for (int i = 0; i < messy.size() - gap; i++) {
          if (messy[i] > messy[i + gap]) {
            std::swap(messy[i], messy[i + gap]);
            swapped = true;
          }
        }
      }
    }
  };
}}}

#endif // __ALGORITHMS__SORTERS__COMB_SORT_H__