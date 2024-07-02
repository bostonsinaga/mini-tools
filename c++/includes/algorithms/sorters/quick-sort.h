#ifndef __ALGORITHMS__SORTERS__QUICK_SORT_H__
#define __ALGORITHMS__SORTERS__QUICK_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  /** Lomuto Partitioning */
  template <class T>
  class Quick {
  private:
    // 'low' and 'high' are index of 'messy'
    static int lomutoPartition(
      std::vector<T> *messy,
      CR_INT low,
      CR_INT high,
      bool &ascending
    );

    static int randomPartition(
      std::vector<T> *messy,
      CR_INT low,
      CR_INT high,
      bool &ascending
    );

    static void recursion(
      std::vector<T> *messy,
      CR_INT low,
      CR_INT high,
      bool &ascending
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