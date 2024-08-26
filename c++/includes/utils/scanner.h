#ifndef __MINI_TOOLS__UTILS__SCANNER_H__
#define __MINI_TOOLS__UTILS__SCANNER_H__

#include "reader.h"

namespace mini_tools {
namespace utils {

  template <class T>
  class Scanner {
  public:
    static T stringToNumber(CR_STR numStr);
    static void parseNumbers(CR_STR text, VEC<T> &vecHook);
    static void parseLetters(CR_STR text, VEC<T> &vecHook);
    static VEC<T> parseNumbers(CR_STR text);
    static VEC<T> parseLetters(CR_STR text);
    static VEC<T> txtToNumbers(CR_STR filename);
    static VEC<T> txtToLetters(CR_STR filename);
  };
}}

#include "scanner.cpp"
#endif // __MINI_TOOLS__UTILS__SCANNER_H__