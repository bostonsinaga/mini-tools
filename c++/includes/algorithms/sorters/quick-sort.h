#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T, class U = std::nullptr_t>
  class Quick {
  private:
    /** Slower */
    static int lomutoPartition(
      std::vector<T> &messy,
      std::vector<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

    /** Faster */
    static int hoarePartition(
      std::vector<T> &messy,
      std::vector<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

    static int randomPartition(
      std::vector<T> &messy,
      std::vector<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending,
      int &scheme
    );

    static void recursion(
      std::vector<T> &messy,
      std::vector<U> *attached,
      CR_INT left,
      CR_INT right,
      bool &ascending,
      int &scheme
    );

  public:
    enum {HOARE, LOMUTO};

    static void solve(
      std::vector<T> &messy,
      std::vector<U> &attached,
      bool ascending = true,
      int scheme = HOARE
    );

    static void solve(
      std::vector<T> &messy,
      bool ascending = true,
      int scheme = HOARE
    );
  };
}}}

#include "quick-sort.cpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_H__