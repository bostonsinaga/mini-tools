#ifndef __MINI_TOOLS__UTILS__TIME_DATE_HPP__
#define __MINI_TOOLS__UTILS__TIME_DATE_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  class TimeDate final {
  private:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock> TP;
    inline static std::chrono::duration<float> difference;
    inline static TP prior;

  public:
    TimeDate() = delete;

    // reset elapsed time
    static void reset();

    // save elapsed time into variables
    static void check();

    /** Elapsed time display in text */

    static float getSeconds(CR_BOL needCheck = true);
    static float getMilliseconds(CR_BOL needCheck = true);

    static void print(
      CR_BOL needCheck = true,
      CR_STR title = "DURATION:",
      CR_BOL inSeconds = false,
      CR_BOL inMilliseconds = true
    );
  };
}}

#endif // __MINI_TOOLS__UTILS__TIME_DATE_HPP__