#ifndef __ALGORITHMS__SORTERS__COMB_SORT_H__
#define __ALGORITHMS__SORTERS__COMB_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T>
  class Comb {
  public:
    static void solve(std::vector<T> *messy);
    static std::vector<T> solve(std::vector<T> messy);
  };
}}}

#include "comb-sort.cpp"
#endif // __ALGORITHMS__SORTERS__COMB_SORT_H__