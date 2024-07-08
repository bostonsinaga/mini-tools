#ifndef __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__
#define __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T>
  class Insertion {
  public:
    static void solve(
      std::vector<T> *messy,
      bool ascending = true
    );

    static std::vector<T> solve(
      std::vector<T> messy,
      bool ascending = true
    );
  };
}}}

#include "insertion-sort.cpp"
#endif // __MINI_TOOLS__ALGORITHMS__SORTERS__INSERTION_SORT_H__