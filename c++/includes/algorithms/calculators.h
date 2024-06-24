#ifndef __ALGORITHMS__CALCULATORS_H__
#define __ALGORITHMS__CALCULATORS_H__

#include <cmath>

namespace mini_tools {
namespace algorithms {
namespace Calc {

  int factorial(int n) {
    int ret = n;

    while (n > 2) {
      ret *= n-1;
      n--;
    }

    return ret;
  }

  /**
   * Stands of parameters:
   *
   * a = first number
   * an = last number
   * d = difference
   * o = order
   * r = ratio
   * q = quantity
   */

  int arithmeticSeries(int a, int an, int q) {
    return q * ((a + an) / 2);
  }

  int geometricSeries(int a, int r, int q) {
    return a * (1 - std::pow(r, q)) / (1 - r);
  }

  int arithmeticSequence(int a, int o, int d) {
    return a + (o - 1) * d;
  }

  int geometricSequence(int a, int r, int o) {
    return a * std::pow(r, o - 1);
  }
}}}

#endif // __ALGORITHMS__CALCULATORS_H__