#ifndef __ALGORITHMS__SORTERS__QUICK_SORT_H__
#define __ALGORITHMS__SORTERS__QUICK_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T>
  class Quick {
  private:
    // 'left' and 'right' are index of 'messy'
    static int partition(
      std::vector<T> *messy,
      CR_INT left,
      CR_INT right,
      bool ascending
    );

    // 'left' and 'right' are index of 'messy'
    static void recursion(
      std::vector<T> *messy,
      CR_INT left,
      CR_INT right,
      bool ascending
    );

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

#include "quick-sort.cpp"
#endif // __ALGORITHMS__SORTERS__QUICK_SORT_H__