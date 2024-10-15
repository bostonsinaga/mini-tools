#ifndef __MINI_TOOLS__UTILS__TIMER_H__
#define __MINI_TOOLS__UTILS__TIMER_H__

#include <chrono>
#include "../types.h"

namespace mini_tools {
namespace utils {

  class Timer {
  private:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP;
    std::chrono::duration<float> difference;
    TP prior;

  public:
    Timer() { reset(); }
    void reset();
    void check();
    float getSeconds(CR_BOL needCheck = true);
    float getMilliseconds(CR_BOL needCheck = true);
    void print(CR_BOL needCheck = true, CR_STR title = "DURATION:");
  };
}}

#endif // __MINI_TOOLS__UTILS__TIMER_H__