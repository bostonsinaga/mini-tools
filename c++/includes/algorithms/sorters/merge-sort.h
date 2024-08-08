#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_SORT_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T, class U = std::nullptr_t>
  class Merge {
  private:
    static void merge(
      std::vector<T> &messy,
      std::vector<U> *attached,
      CR_INT left,
      CR_INT mid,
      CR_INT right,
      bool &ascending
    );

    static void partition(
      std::vector<T> &messy,
      std::vector<U> *attached,
      CR_INT begin,
      CR_INT end,
      bool &ascending
    );

  public:
    static void solve(
      std::vector<T> &messy,
      std::vector<U> &attached,
      bool ascending = true
    );

    static void solve(
      std::vector<T> &messy,
      bool ascending = true
    );
  };
}}}

#include "merge-sort.cpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_SORT_H__