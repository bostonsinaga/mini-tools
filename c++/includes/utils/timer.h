#ifndef __MINI_TOOLS__UTILS__TIMER_H__
#define __MINI_TOOLS__UTILS__TIMER_H__

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
    float getSeconds(bool needCheck = true);
    float getMilliseconds(bool needCheck = true);
    void print(bool needCheck = true, std::string title = "DURATION:");
  };
}}

#endif // __MINI_TOOLS__UTILS__TIMER_H__