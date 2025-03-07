#ifndef __MINI_TOOLS__SORTERS__MERGE_SORT_H__
#define __MINI_TOOLS__SORTERS__MERGE_SORT_H__

namespace mini_tools {
namespace sorters {

  template <class T, class U = std::nullptr_t>
  class Merge {
  private:
    static void merge(
      VEC<T> &messy,
      VEC<U> *attached,
      CR_INT left,
      CR_INT mid,
      CR_INT right,
      bool &ascending
    );

    static void partition(
      VEC<T> &messy,
      VEC<U> *attached,
      CR_INT begin,
      CR_INT end,
      bool &ascending
    );

  public:
    static void solve(
      VEC<T> &messy,
      VEC<U> &attached,
      bool ascending = true
    );

    static void solve(
      VEC<T> &messy,
      bool ascending = true
    );
  };
}}

#include "sorters/merge-sort.tpp"
#endif // __MINI_TOOLS__SORTERS__MERGE_SORT_H__