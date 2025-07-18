#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_HPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_HPP__

#include "types.hpp"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, class U, QUICK_SCHEME_ENUM SCHEME = QUICK_HOARE>
  class Quick final {
  private:
    /** Slower */
    static int lomutoPartition(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order,
      CR_INT left,
      CR_INT right
    );

    /** Faster */
    static int hoarePartition(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order,
      CR_INT left,
      CR_INT right
    );

    static int randomPartition(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order,
      CR_INT left,
      CR_INT right
    );

    static void recursion(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order,
      CR_INT left,
      CR_INT right
    );

  public:
    Quick() = delete;

    static void solve(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order = ORDER_ASCENDING
    );
  };
}}}

#include "algorithms/sorters/quick.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__QUICK_HPP__