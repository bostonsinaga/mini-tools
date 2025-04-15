#ifndef __MINI_TOOLS__UTILS__TIME_DATE_CPP__
#define __MINI_TOOLS__UTILS__TIME_DATE_CPP__

#include "types.h"
#include "utils/time-date.h"

namespace mini_tools {
namespace utils {

  void TimeDate::reset() {
    prior = std::chrono::high_resolution_clock::now();
    difference = std::chrono::nanoseconds::zero();
  }

  void TimeDate::check() {
    TP now = std::chrono::high_resolution_clock::now();
    difference = now - prior;
    prior = now;
  }

  float TimeDate::getSeconds(CR_BOL needCheck) {
    if (needCheck) check();
    return difference.count();
  }

  float TimeDate::getMilliseconds(CR_BOL needCheck) {
    if (needCheck) check();
    return std::chrono::duration_cast<std::chrono::milliseconds>(difference).count();
  }

  void TimeDate::print(CR_BOL needCheck, CR_STR title) {
    if (needCheck) check();
    std::cout << title << std::endl;
    std::cout << getSeconds(false) << "s\n";
    std::cout << getMilliseconds(false) << "ms\n";
  }
}}

#endif // __MINI_TOOLS__UTILS__TIME_DATE_CPP__