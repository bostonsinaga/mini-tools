#ifndef __MINI_TOOLS__UTILS__READER_H__
#define __MINI_TOOLS__UTILS__READER_H__

#include <fstream>
#include "../types.h"

namespace mini_tools {
namespace utils {

  class Reader {
  public:
    static bool isSeparator(CR_CHR ch) {
      if (ch == ' ' || ch == ',' || ch == '\n') return true;
      return false;
    }

    static bool isSeparator(CR_STR text, CR_INT i) {
      if (i >= 0 && i < text.length()) {
        if (isSeparator(text[i]) || i == text.length() - 1) {
          return true;
        }
        return false;
      }
      return false;
    }

    /** WARNING. Unable to read '\n' character */
    static void getFrom(
      CR_STR filename,
      std::string &textHook
    ) {
      std::string line;
      std::ifstream reader(filename);
      while (std::getline(reader, line)) { textHook += line; }
      reader.close();
    }
  };

  template <class T>
  class Scanner {
  public:
    static void parseNumbers(CR_STR text, VEC<T> &vecHook);
    static void parseLetters(CR_STR text, VEC<T> &vecHook);

    static VEC<T> parseNumbers(CR_STR text);
    static VEC<T> parseLetters(CR_STR text);

    static VEC<T> txtToNumbers(CR_STR filename);
    static VEC<T> txtToLetters(CR_STR filename);
  };
}}

#include "reader.cpp"
#endif // __MINI_TOOLS__UTILS__READER_H__