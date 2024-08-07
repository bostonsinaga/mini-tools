#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T>
  class Quick {
  private:
    static int lomutoPartition(
      std::vector<T> *messy,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

    static int hoarePartition(
      std::vector<T> *messy,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

    static int randomPartition(
      std::vector<T> *messy,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

    static void recursion(
      std::vector<T> *messy,
      CR_INT left,
      CR_INT right,
      bool &ascending
    );

  public:
    enum {HOARE, LOMUTO};

    static void solve(
      std::vector<T> *messy,
      bool ascending = true,
      int scheme = HOARE
    );

    static std::vector<T> solve(
      std::vector<T> messy,
      bool ascending = true,
      int scheme = HOARE
    );
  };
}}}

#include "quick-sort.cpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_SORT_H__