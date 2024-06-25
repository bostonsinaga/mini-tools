#ifndef __ALGORITHMS__CALCULATORS_H__
#define __ALGORITHMS__CALCULATORS_H__

#include <cmath>
#include <vector>
#include <algorithms>

namespace mini_tools {
namespace algorithms {
  class Calc {
  public:
    static int factorial(int n) {
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

    static int arithmeticSeries(int a, int an, int q) {
      return q * ((a + an) / 2);
    }

    static int geometricSeries(int a, int r, int q) {
      return a * (1 - std::pow(r, q)) / (1 - r);
    }

    static int arithmeticSequence(int a, int o, int d) {
      return a + (o - 1) * d;
    }

    static int geometricSequence(int a, int r, int o) {
      return a * std::pow(r, o - 1);
    }

    static bool isArithmeticSequence(std::vector<int> nums, int d) {
      for (int i = 0; i < nums.size() - 1; i++) {
        if (nums[i] + d != nums[i+1]) return false;
      }
      return true;
    }

    static bool isGeometricSequence(std::vector<int> nums, int r) {
      for (int i = 0; i < nums.size() - 1; i++) {
        if (nums[i] * r != nums[i+1]) return false;
      }
      return true;
    }

  private:
    static void limitPartialSortedTestCount(
      const int &totalCount,
      int &partialTestCount
    ) {
      if (partialTestCount <= 0) {
        partialTestCount = totalCount - 1;
      }
      else if (partialTestCount > totalCount - 1) {
        partialTestCount = totalCount - 1;
      }
    }

  public:
    static bool isSorted(
      std::vector<int> &nums,
      bool ascending = true,
      int partialTestCount = 0
    ) {
      limitPartialSortedTestCount(nums.size(), partialTestCount);
      int last = nums.size() - 1;

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

      return true;
    }
  };
}}

#endif // __ALGORITHMS__CALCULATORS_H__