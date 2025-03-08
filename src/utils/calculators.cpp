#ifndef __MINI_TOOLS__ALGORITHMS__CALCULATORS_CPP__
#define __MINI_TOOLS__ALGORITHMS__CALCULATORS_CPP__

#include <cmath>
#include <algorithm>
#include "utils/calculators.h"

namespace mini_tools {
namespace utils {

  int Calc::factorial(int n) {
    int ret = n;

    while (n > 2) {
      ret *= n-1;
      n--;
    }

    return ret;
  }

  int Calc::arithmeticSeries(
    CR_INT a, CR_INT an, CR_INT q
  ) { return q * ((a + an) / 2); }

  int Calc::geometricSeries(
    CR_INT a, CR_INT r, CR_INT q
  ) { return a * (1 - std::pow(r, q)) / (1 - r); }

  int Calc::arithmeticSequence(
    CR_INT a, CR_INT o, CR_INT d
  ) { return a + (o - 1) * d; }

  int Calc::geometricSequence(
    CR_INT a, CR_INT r, CR_INT o
  ) { return a * std::pow(r, o - 1); }

  bool Calc::isArithmeticSequence(
    VEC_INT &nums, CR_INT d
  ) {
    if (nums.size() == 0) return false;

    for (int i = 0; i < nums.size() - 1; i++) {
      if (nums[i] + d != nums[i+1]) return false;
    }

    return true;
  }

  bool Calc::isArithmeticSequence(
    CR_VEC_INT nums, CR_INT d
  ) {
    if (nums.size() == 0) return false;

    for (int i = 0; i < nums.size() - 1; i++) {
      if (nums[i] + d != nums[i+1]) return false;
    }

    return true;
  }

  bool Calc::isGeometricSequence(
    VEC_INT &nums, CR_INT r
  ) {
    if (nums.size() == 0) return false;

    for (int i = 0; i < nums.size() - 1; i++) {
      if (nums[i] * r != nums[i+1]) return false;
    }

    return true;
  }

  bool Calc::isGeometricSequence(
    CR_VEC_INT nums, CR_INT r
  ) {
    if (nums.size() == 0) return false;

    for (int i = 0; i < nums.size() - 1; i++) {
      if (nums[i] * r != nums[i+1]) return false;
    }

    return true;
  }

  bool Calc::isSorted(
    VEC_INT &nums,
    CR_BOL ascending,
    CR_INT startIndex,
    int partialTestCount,
    int skipTestCount
  ) {
    int last = nums.size() - 1;
    if (last < 0) return true;

    std::function<void()> limitPartialTestCount = [&]() {
      if (partialTestCount <= 0 ||
        partialTestCount > nums.size()
      ) { partialTestCount = nums.size(); }
    };

    // bad arguments
    if (startIndex < 0 || startIndex > last) return false;
    limitPartialTestCount();

    // this function will not change the 'nums'
    std::vector<int> backup;

    if (skipTestCount > 0) {

      // limit 'skipTestCount'
      if (skipTestCount + startIndex > last) {
        skipTestCount = last - startIndex;
      }

      backup = nums;
      nums = {};

      // skip 'nums'
      for (int i = startIndex; i <= last; i += skipTestCount + 1) {
        nums.push_back(backup[i]);
      }

      last = nums.size() - 1;
      limitPartialTestCount();
    }

    if (startIndex >= last) return true;
    partialTestCount--;

    for (int i = 0; i < last; i += partialTestCount) {

      int nextCount = i + partialTestCount;
      if (nextCount > last) nextCount = last;

      if (ascending) {
        if (!std::is_sorted(
          nums.begin() + i, nums.begin() + nextCount + 1
        )) { return false; }
      }
      else {
        if (!std::is_sorted(
          nums.begin() + i, nums.begin() + nextCount + 1, std::greater<int>()
        )) { return false; }
      }
    }

    if (backup.size() > 0) nums = backup;
    return true;
  }
}}

#endif // __MINI_TOOLS__ALGORITHMS__CALCULATORS_CPP__