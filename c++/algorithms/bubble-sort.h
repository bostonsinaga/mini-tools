#ifndef __SORTERS__BUBBLE_SORT_H__
#define __SORTERS__BUBBLE_SORT_H__

namespace sorter {

  class Bubble {
  public:
    static int solve(std::vector<int> &messy) {
      int ctr = 0;

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

        ctr++;
        if (breakLoop) break;
      }

      return ctr;
    }
  };
}

#endif // __SORTERS__BUBBLE_SORT_H__