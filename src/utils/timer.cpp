#ifndef __MINI_TOOLS__UTILS__TIMER_CPP__
#define __MINI_TOOLS__UTILS__TIMER_CPP__

#include "utils/timer.h"

namespace mini_tools {
namespace utils {

  void Timer::reset() {
    prior = std::chrono::high_resolution_clock::now();
    difference = std::chrono::nanoseconds::zero();
  }

  void Timer::check() {
    TP now = std::chrono::high_resolution_clock::now();
    difference = now - prior;
    prior = now;
  }

  float Timer::getSeconds(CR_BOL needCheck) {
    if (needCheck) check();
    return difference.count();
  }

  float Timer::getMilliseconds(CR_BOL needCheck) {
    if (needCheck) check();
    return std::chrono::duration_cast<std::chrono::milliseconds>(difference).count();
  }

  void Timer::print(CR_BOL needCheck, CR_STR title) {
    if (needCheck) check();
    std::cout << title << std::endl;
    std::cout << getSeconds(false) << "s\n";
    std::cout << getMilliseconds(false) << "ms\n";
  }
}}

#endif // __MINI_TOOLS__UTILS__TIMER_CPP__