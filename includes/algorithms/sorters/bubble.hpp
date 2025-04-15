#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_H__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, class U>
  class Bubble {
  private:
    static void process(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM ascending
    );

  public:
    static void solve(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM ascending = ORDER_ASCENDING
    );
  };
}}}

#include "algorithms/sorters/bubble.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__BUBBLE_H__