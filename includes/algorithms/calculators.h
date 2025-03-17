#ifndef __MINI_TOOLS__ALGORITHMS__CALCULATORS_H__
#define __MINI_TOOLS__ALGORITHMS__CALCULATORS_H__

#include "types.h"

namespace mini_tools {
namespace algorithms {

  class Calc {
  public:
    /**
     * Stands of parameters:
     *  n = number
     *  a = first number
     *  an = last number
     *  d = difference
     *  o = order
     *  r = ratio
     *  q = quantity
     */

    static int factorial(int n);

    static int arithmeticSeries(
      CR_INT a, CR_INT an, CR_INT q
    );

    static int geometricSeries(
      CR_INT a, CR_INT r, CR_INT q
    );

    static int arithmeticSequence(
      CR_INT a, CR_INT o, CR_INT d
    );

    static int geometricSequence(
      CR_INT a, CR_INT r, CR_INT o
    );

    static bool isArithmeticSequence(
      VEC_INT &nums, CR_INT d
    );

    static bool isArithmeticSequence(
      CR_VEC_INT nums, CR_INT d
    );

    static bool isGeometricSequence(
      VEC_INT &nums, CR_INT r
    );

    static bool isGeometricSequence(
      CR_VEC_INT nums, CR_INT r
    );

    /**
     * Returns true if 'nums' is single
     * or 'startIndex' is the last when 'ascending' true
     * or 'startIndex' is the first when 'ascending' false
     */
    static bool isSorted(
      VEC_INT &nums,
      CR_BOL ascending = true,
      CR_INT startIndex = 0,
      int partialTestCount = 0,
      int skipTestCount = 0
    );
  };
}}

#endif // __MINI_TOOLS__ALGORITHMS__CALCULATORS_H__