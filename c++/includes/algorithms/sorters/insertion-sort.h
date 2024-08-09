#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T, class U = std::nullptr_t>
  class Insertion {
  protected:
    static void process(
      std::vector<T> &messy,
      std::vector<U> *attached,
      bool &ascending,
      CR_INT start, CR_INT end
    );

  public:
    static void solve(
      std::vector<T> &messy,
      std::vector<U> &attached,
      CR_BOL ascending = true
    );

    static void solve(
      std::vector<T> &messy,
      CR_BOL ascending = true
    );

    friend class Quick;
  };
}}}

#include "insertion-sort.cpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__