#ifndef __MINI_TOOLS__UTILS__READER_CPP__
#define __MINI_TOOLS__UTILS__READER_CPP__

#include <fstream>
#include "types.h"
#include "utils/reader.h"

namespace mini_tools {
namespace utils {

  VEC_CH Reader::separators_ch {' ', ',', '\n'};
  VEC_STR Reader::separators_str {" ", ",", "\n"};

  bool Reader::isSeparator(CR_CH ch) {
    for (CR_CH c : separators_ch) {
      if (ch == c) return true;
    }
    return false;
  }

  bool Reader::isSeparator(CR_STR str) {
    for (CR_STR s : separators_str) {
      if (str == s) return true;
    }
    return false;
  }

  bool Reader::isSeparator(CR_STR text, CR_INT idx) {
    if (idx >= 0 && idx < text.length()) {
      if (Reader::isSeparator(text[idx]) ||
        idx == text.length() - 1
      ) {
        return true;
      }
      return false;
    }
    return false;
  }

  bool Reader::isSeparator(CR_VEC_STR textVec, CR_INT idx) {
    if (idx >= 0 && idx < textVec.size()) {
      if (Reader::isSeparator(textVec[idx]) ||
        idx == text.length() - 1
      ) {
        return true;
      }
      return false;
    }
    return false;
  }

  /** WARNING. Unable to read '\n' character */
  void Reader::getFile(
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