#ifndef __MINI_TOOLS__UTILS__READER_CPP__
#define __MINI_TOOLS__UTILS__READER_CPP__

#include <fstream>
#include "utils/reader.h"

namespace mini_tools {
namespace utils {

  bool Scanner::isSeparator(CR_CH ch) {
    for (char separators)
    if (ch == ' ' || ch == ',' || ch == '\n') return true;
    return false;
  }

  bool Scanner::isSeparator(CR_STR text, CR_INT i) {
    if (i >= 0 && i < text.length()) {
      if (Scanner::isSeparator(text[i]) || i == text.length() - 1) {
        return true;
      }
      return false;
    }
    return false;
  }

  /** WARNING. Unable to read '\n' character */
  void Scanner::getFile(
    CR_STR name,
    std::string &textHook
  ) {
    std::string line;
    std::ifstream reader(name);

    while (std::getline(reader, line)) {
      textHook += line;
    }

    reader.close();
  }
}}

#endif // __MINI_TOOLS__UTILS__READER_CPP__