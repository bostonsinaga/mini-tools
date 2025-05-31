#ifndef __MINI_TOOLS__ALGORITHMS__NUMBER_SEQUENCE_HPP__
#define __MINI_TOOLS__ALGORITHMS__NUMBER_SEQUENCE_HPP__

#include "types.hpp"

namespace mini_tools {
namespace algorithms {

  class NumberSequence final {
  public:
    /**
     * Stands of parameters:
     *  n  = number
     *  a  = first number
     *  an = last number
     *  d  = difference
     *  o  = order
     *  r  = ratio
     *  q  = quantity
     */

    NumberSequence() = delete;
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

    /**
     * You can sum this return with the return of 'countDecimalPlaces'
     * to get the full number of digits and +1 for decimal point sign.
     */
    template <inspector::INTEGRAL T>
    static int countDigits(CR<T> number) {
      return (number == 0) ? 1 : std::log10(std::abs(number)) + 1;
    }

    /**
     * Floating point precisions based on IEEE 754 standard:
     * - Float = 6-7 digits.
     * - Double = 15-17 digits.
     * - Long Double = 19-21 digits.
     * 
     * You can specify the 'precision'
     * with 'PRECISION_ENUM' from 'types.hpp'
     * which stores the above standards.
     */
    template <inspector::FLOATING_POINT T>
    static int countDecimalPlaces(
      T number,
      CR_USI precision = 6
    ) {
      int count = 0;

      while (count < precision &&
        number != static_cast<int>(number)
      ) {
        number *= 10;
        count++;
      }

      return count;
    }
  };
}}

#endif // __MINI_TOOLS__ALGORITHMS__NUMBER_SEQUENCE_HPP__