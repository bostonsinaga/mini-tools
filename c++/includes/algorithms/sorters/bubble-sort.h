#ifndef __ALGORITHMS__SORTERS__BUBBLE_SORT_H__
#define __ALGORITHMS__SORTERS__BUBBLE_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  class Bubble {
  public:
    static void solve(VEC_INT &messy) {
      bool stop = false;

      while (!stop) {
        stop = true;
        int i = 0;

        for (int j = 1; j < messy.size(); j++) {

          if (messy[j] < messy[i]) {
            stop = false;
            std::swap(messy[j], messy[i]);
          }

          i = j;
        }

        if (stop) break;
      }
    }
  };
}}}

#endif // __ALGORITHMS__SORTERS__BUBBLE_SORT_H__