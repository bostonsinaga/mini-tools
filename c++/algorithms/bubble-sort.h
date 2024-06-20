#ifndef __SORTERS__BUBBLE_SORT_H__
#define __SORTERS__BUBBLE_SORT_H__

namespace sorter {

  class BubbleSort {
  public:
    static void solve(std::vector<int> &messy) {
      for (int i = 0; i < messy.size(); i++) {

        bool breakLoop = true;
        int k = 0;

        for (int j = 1; j < messy.size(); j++) {

          if (messy[j] < messy[k]) {
            breakLoop = false;

            int buffer = messy[k];
            messy[k] = messy[j];
            messy[j] = buffer;
          }
          else k = j;
        }
        
        utils::Printer::log(messy, i, utils::Printer::BAR_STYLE);
        if (breakLoop) break;
      }
    }
  };
}

#endif // __SORTERS__BUBBLE_SORT_H__