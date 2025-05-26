#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_HPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_HPP__

#include "types.hpp"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, class U>
  class Comb final {
  private:
    static void process(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM ascending
    );

  public:
    Comb() = delete;

    static void solve(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM ascending = ORDER_ASCENDING
    );
  };
}}}

#include "algorithms/sorters/comb.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_HPP__