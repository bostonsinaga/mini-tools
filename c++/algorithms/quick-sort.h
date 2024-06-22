#ifndef __SORTERS__QUICK_SORT_H__
#define __SORTERS__QUICK_SORT_H__

namespace sorter {

  class Quick {
  private:
    // 'left' and 'right' are index of 'messy'
    static int partition(
      std::vector<int> &messy, int left, int right
    ) {
      int i = left - 1;

      for (int j = left; j < right; j++) {
        if (messy[j] < messy[right]) {
          i++;
          std::swap(messy[i], messy[j]);
        }
      }

      std::swap(messy[i+1], messy[right]);
      return i+1;
    }

    // 'left' and 'right' are index of 'messy'
    static void recursion(
      std::vector<int> &messy, int left, int right
    ) {
      if (left < right) {
        int piv = partition(messy, left, right);
        recursion(messy, left, piv - 1);
        recursion(messy, piv + 1, right);
      }
    }

  public:
    static void solve(std::vector<int> &messy) {
      recursion(messy, 0, messy.size() - 1);
    }
  };
}

#endif // __SORTERS__QUICK_SORT_H__