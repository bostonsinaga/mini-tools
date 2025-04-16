#ifndef __MINI_TOOLS__UTILS__TIME_DATE_CPP__
#define __MINI_TOOLS__UTILS__TIME_DATE_CPP__

#include "types.hpp"
#include "utils/time_date.hpp"

namespace mini_tools {
namespace utils {

  void TimeDate::reset() {
    TimeDate::prior = std::chrono::high_resolution_clock::now();
    TimeDate::difference = std::chrono::nanoseconds::zero();
  }

  void TimeDate::check() {
    TP now = std::chrono::high_resolution_clock::now();
    TimeDate::difference = now - TimeDate::prior;
    TimeDate::prior = now;
  }

  float TimeDate::getSeconds(CR_BOL needCheck) {
    if (needCheck) TimeDate::check();
    return TimeDate::difference.count();
  }

  float TimeDate::getMilliseconds(CR_BOL needCheck) {
    if (needCheck) TimeDate::check();

    return std::chrono::duration_cast<std::chrono::milliseconds>(
      TimeDate::difference
    ).count();
  }

  void TimeDate::print(
    CR_BOL needCheck, CR_STR title,
    CR_BOL inSeconds, CR_BOL inMilliseconds
  ) {
    if (needCheck) TimeDate::check();

    // title
    std::cout << title << std::endl;

    // seconds
    if (inSeconds || !(inSeconds || inMilliseconds)) {
      std::cout << TimeDate::getSeconds(false) << "s\n";
    }
    // milliseconds
    else std::cout << TimeDate::getMilliseconds(false) << "ms\n";
  }
}}

#endif // __MINI_TOOLS__UTILS__TIME_DATE_CPP__