#ifndef __ALGORITHMS__SORTERS__BUBBLE_SORT_H__
#define __ALGORITHMS__SORTERS__BUBBLE_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  class Bubble {
  public:
    static void solve(VEC_INT &messy) {

      for (int i = 0; i < messy.size(); i++) {
        bool breakLoop = true;
        int k = 0;

        for (int j = 1; j < messy.size(); j++) {

          if (messy[j] < messy[k]) {
            breakLoop = false;
            std::swap(messy[j], messy[k]);
          }

          k = j;
        }

        if (breakLoop) break;
      }
    }
  };
}}}

#endif // __ALGORITHMS__SORTERS__BUBBLE_SORT_H__