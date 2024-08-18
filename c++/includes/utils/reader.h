#ifndef __MINI_TOOLS__UTILS__READER_H__
#define __MINI_TOOLS__UTILS__READER_H__

#include "../types.h"

namespace mini_tools {
namespace utils {

  class Reader {
  public:
    static bool isSeparator(CR_CHR ch);
    static bool isSeparator(CR_STR text, CR_INT i);

    /** WARNING. Unable to read '\n' character */
    static void getFile(
      CR_STR name,
      std::string &textHook
    );

    template <typename T>
    static T stringToNumber(CR_STR numStr);

    template <typename T>
    static void parseNumbers(CR_STR text, VEC<T> &vecHook);

    template <typename T>
    static void parseLetters(CR_STR text, VEC<T> &vecHook);

    template <typename T>
    static VEC<T> parseNumbers(CR_STR text);

    template <typename T>
    static VEC<T> parseLetters(CR_STR text);

    template <typename T>
    static VEC<T> txtToNumbers(CR_STR filename);

    template <typename T>
    static VEC<T> txtToLetters(CR_STR filename);
  };
}}

#include "reader.cpp"
#endif // __MINI_TOOLS__UTILS__READER_H__