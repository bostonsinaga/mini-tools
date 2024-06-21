#ifndef __UTILS__PRINTER_H__
#define __UTILS__PRINTER_H__

#include <iostream>
#include <vector>

namespace util {

  class Printer {
  public:
    enum {BAR_STYLE, NUMBER_STYLE};

    static void log(std::vector<int> &nums, int step, bool style) {
      std::cout << "Step: " << step << std::endl;

      for (int i = 0; i < nums.size(); i++) {

        if (style) std::cout << nums[i] << ',';
        else {
          for (int j = 0; j < nums[i]; j++) {
            std::cout << "[]";
          }
        }

        std::cout << std::endl;
      }
    }
  };
}

#endif // __UTILS__PRINTER_H__