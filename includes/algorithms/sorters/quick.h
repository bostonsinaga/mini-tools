#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_H__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, class U, QUICK_SCHEME_ENUM SCHEME = QUICK_HOARE>
  class Quick {
  private:
    /** Slower */
    static int lomutoPartition(
      VEC_PAIR2<T, U> &messy,
      CR_INT left,
      CR_INT right,
      CR_ORDER_ENUM order
    );

    /** Faster */
    static int hoarePartition(
      VEC_PAIR2<T, U> &messy,
      CR_INT left,
      CR_INT right,
      CR_ORDER_ENUM order
    );

    static int randomPartition(
      VEC_PAIR2<T, U> &messy,
      CR_INT left,
      CR_INT right,
      CR_ORDER_ENUM order
    );

    static void recursion(
      VEC_PAIR2<T, U> &messy,
      CR_INT left,
      CR_INT right,
      CR_ORDER_ENUM order
    );

  public:
    static void solve(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order = ORDER_ASCENDING
    );
  };
}}}

#include "algorithms/sorters/quick.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_H__