#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_H__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T, class U = std::nullptr_t>
  class Comb {
    static void process(
      VEC<T> &messy,
      VEC<U> *attached,
      bool &ascending
    );

  public:
    static void solve(
      VEC<T> &messy,
      VEC<U> &attached,
      bool ascending = true
    );

    static void solve(
      VEC<T> &messy,
      bool ascending = true
    );
  };
}}}

#include "algorithms/sorters/comb.tpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__COMB_H__