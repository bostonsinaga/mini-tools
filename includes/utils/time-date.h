#ifndef __MINI_TOOLS__UTILS__TIME_DATE_H__
#define __MINI_TOOLS__UTILS__TIME_DATE_H__

#include <chrono>

namespace mini_tools {
namespace utils {

  class TimeDate {
  private:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP;
    std::chrono::duration<float> difference;
    TP prior;

  public:
    TimeDate() { reset(); }
    void reset();
    void check();
    float getSeconds(CR_BOL needCheck = true);
    float getMilliseconds(CR_BOL needCheck = true);
    void print(CR_BOL needCheck = true, CR_STR title = "DURATION:");
  };
}}

#endif // __MINI_TOOLS__UTILS__TIME_DATE_H__