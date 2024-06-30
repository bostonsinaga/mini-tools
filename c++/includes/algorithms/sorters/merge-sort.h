#ifndef __ALGORITHMS__SORTERS__MERGE_SORT_H__
#define __ALGORITHMS__SORTERS__MERGE_SORT_H__

#include "../../types.h"

namespace mini_tools {
namespace algorithms {
namespace sorters {

  template <class T>
  class Merge {
  private:
    static void merge(std::vector<T> *messy, CR_INT left, CR_INT mid, CR_INT right);
    static void partition(std::vector<T> *messy, CR_INT begin, CR_INT end);

  public:
    static void solve(std::vector<T> *messy);
    static std::vector<T> solve(std::vector<T> messy);
  };
}}}

#include "merge-sort.cpp"
#endif // __ALGORITHMS__SORTERS__MERGE_SORT_H__