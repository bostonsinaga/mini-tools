#ifndef __ALGORITHMS__BUBBLE_SORT_H__
#define __ALGORITHMS__BUBBLE_SORT_H__

namespace sorter {

  class Bubble {
  public:
    static void solve(std::vector<int> &messy) {

      for (int i = 0; i < messy.size(); i++) {
        bool breakLoop = true;
        int k = 0;

        for (int j = 1; j < messy.size(); j++) {

          if (messy[j] < messy[k]) {
            breakLoop = false;
            std::swap(messy[j], messy[k]);
          }

          k = j;
        }

        if (breakLoop) break;
      }
    }
  };
}

#endif // __ALGORITHMS__BUBBLE_SORT_H__