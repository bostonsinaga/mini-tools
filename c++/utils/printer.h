#ifndef __UTILS__PRINTER_H__
#define __UTILS__PRINTER_H__

#include <iostream>
#include <vector>

namespace util {

  class Printer {
  public:
    enum {BAR_STYLE, NUMBER_STYLE};

    static void log(
      std::vector<int> &nums,
      bool style,
      int step,
      std::string title = "Step"
    ) {
      if (step >= 0) {
        std::cout << title << ": " << step << std::endl;
      }
      else std::cout << title << ": " << std::endl;

      for (int i = 0; i < nums.size(); i++) {
        if (style) {
          std::cout << nums[i] << (i < nums.size() - 1 ? ", " : "\n");
        }
        else std::cout << std::string(nums[i], '=') << std::endl;
      }
    }

    static void log(
      std::vector<int> &nums,
      bool style,
      std::string title = "Result"
    ) {
      log(nums, style, -1, title);
    }
  };
}

#endif // __UTILS__PRINTER_H__