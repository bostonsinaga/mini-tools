#ifndef __ALGORITHMS__CALCULATORS_H__
#define __ALGORITHMS__CALCULATORS_H__

#include <cmath>
#include "../types.h"

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

  int arithmeticSeries(int a0, int an, int n) {
    return n * ((a0 + an) / 2);
  }

  int geometricSeries(int a0, int r, int n) {
    return a0 * (1 - std::pow(r, n)) / (1 - r);
  }
}}}

#endif // __ALGORITHMS__CALCULATORS_H__