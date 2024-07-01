#ifndef __ALGORITHMS__SORTERS__BUBBLE_SORT_H__
#define __ALGORITHMS__SORTERS__BUBBLE_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T>
  class Bubble {
  public:
    static void solve(
      std::vector<T> *messy,
      bool ascending = true
    );

    static std::vector<T> solve(
      std::vector<T> messy,
      bool ascending = true
    );
  };
}}}

#include "bubble-sort.cpp"
#endif // __ALGORITHMS__SORTERS__BUBBLE_SORT_H__