#ifndef __MINI_TOOLS__SORTERS__QUICK_SORT_H__
#define __MINI_TOOLS__SORTERS__QUICK_SORT_H__

namespace mini_tools {
namespace sorters {

  template <class T, class U = std::nullptr_t>
  class Quick {
  private:
    /** Slower */
    static int lomutoPartition(
      VEC<T> &messy,
      VEC<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

    /** Faster */
    static int hoarePartition(
      VEC<T> &messy,
      VEC<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

    static int randomPartition(
      VEC<T> &messy,
      VEC<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending,
      int &scheme
    );

    static void recursion(
      VEC<T> &messy,
      VEC<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending,
      int &scheme
    );

  public:
    enum {HOARE, LOMUTO};

    static void solve(
      VEC<T> &messy,
      VEC<U> &attached,
      bool ascending = true,
      int scheme = HOARE
    );

    static void solve(
      VEC<T> &messy,
      bool ascending = true,
      int scheme = HOARE
    );
  };
}}

#include "sorters/quick-sort.tpp"
#endif // __MINI_TOOLS__SORTERS__QUICK_SORT_H__