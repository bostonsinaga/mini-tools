#ifndef __MINI_TOOLS__UTILS__READER_H__
#define __MINI_TOOLS__UTILS__READER_H__

#include <fstream>

namespace mini_tools {
namespace utils {

  class Reader {
  public:
    static bool isSeparator(CR_CHR ch) {
      if (ch == ' ' || ch == ',' || ch == '\n') return true;
      return false;
    }

    static bool isSeparator(CR_STR text, CR_INT i) {
      if (isSeparator(text[i]) || i == text.length() - 1) return true;
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
    static std::vector<T> txtToNumbers(std::string filename);
    static std::vector<T> txtToLetters(std::string filename);
  };
}}

#include "reader.cpp"
#endif // __MINI_TOOLS__UTILS__READER_H__