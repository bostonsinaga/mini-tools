#ifndef __MINI_TOOLS__ALGORITHMS__EQUAL_DISTRIBUTION_H__
#define __MINI_TOOLS__ALGORITHMS__EQUAL_DISTRIBUTION_H__

namespace mini_tools {
namespace algorithms {

  class EqualDistribution {
  public:
    template <typename T>
    static void balance(VEC2<T> containers, VEC<T> contents);

  };
}}

#endif // __MINI_TOOLS__ALGORITHMS__EQUAL_DISTRIBUTION_H__