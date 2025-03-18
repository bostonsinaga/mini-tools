#ifndef __MINI_TOOLS__UTILS__SCANNER_CPP__
#define __MINI_TOOLS__UTILS__SCANNER_CPP__

#include <fstream>
#include "types.h"
#include "utils/scanner.h"

namespace mini_tools {
namespace utils {

  bool Scanner::isSeparator(CR_CH ch) {
    for (CR_CH c : separators_ch) {
      if (ch == c) return true;
    }
    return false;
  }

  bool Scanner::isSeparator(CR_STR str) {
    for (CR_STR s : separators_str) {
      if (str == s) return true;
    }
    return false;
  }

  bool Scanner::isSeparator(CR_STR text, CR_INT idx) {
    if (idx >= 0 && idx < text.length()) {
      if (Scanner::isSeparator(text[idx]) ||
        idx == text.length() - 1
      ) {
        return true;
      }
      return false;
    }
    return false;
  }

  bool Scanner::isSeparator(CR_VEC_STR textVec, CR_INT idx) {
    if (idx >= 0 && idx < textVec.size()) {
      if (Scanner::isSeparator(textVec[idx]) ||
        idx == text.length() - 1
      ) {
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

#endif // __MINI_TOOLS__UTILS__SCANNER_CPP__