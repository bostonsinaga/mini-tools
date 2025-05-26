#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_HPP__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_HPP__

#include "types.hpp"
#include "utils/vec-tools.hpp"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <inspector::NUMBER T, class U>
  class Merge final {
  private:
    static void merge(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order,
      CR_INT left,
      CR_INT mid,
      CR_INT right
    );

    static void partition(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order,
      CR_INT begin,
      CR_INT end
    );

  public:
    Merge() = delete;

    static void solve(
      VEC_PAIR2<T, U> &messy,
      CR_ORDER_ENUM order = ORDER_ASCENDING
    );
  };
}}}

#include "algorithms/sorters/merge.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__MERGE_HPP__