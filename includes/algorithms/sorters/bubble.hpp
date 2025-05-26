#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_HPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_HPP__

#include "types.hpp"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, class U>
  class Bubble final {
  private:
    static void process(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM ascending
    );

  public:
    Bubble() = delete;

    static void solve(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM ascending = ORDER_ASCENDING
    );
  };
}}}

#include "algorithms/sorters/bubble.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_HPP__