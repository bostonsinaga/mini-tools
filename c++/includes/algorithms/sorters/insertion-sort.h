#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T, class U = std::nullptr_t>
  class Insertion {
  protected:
    static void process(
      VEC<T> &messy,
      VEC<U> *attached,
      CR_BOL ascending,
      CR_INT start, CR_INT end
    );

  public:
    static void solve(
      VEC<T> &messy,
      VEC<U> &attached,
      CR_BOL ascending = true
    );

    static void solve(
      VEC<T> &messy,
      CR_BOL ascending = true
    );

    template<typename, typename>
    friend class Quick;
  };
}}}

#include "insertion-sort.cpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__