#ifndef __MINI_TOOLS__UTILS__SCANNER_CPP__
#define __MINI_TOOLS__UTILS__SCANNER_CPP__

#include "utils/scanner.hpp"

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
        idx == textVec.size() - 1
      ) {
        return true;
      }
      return false;
    }
    return false;
  }

  std::string Scanner::readFileString(CR_FS_PATH path) {
    std::string text, line;
    std::ifstream input(path);

    while (std::getline(input, line)) {
      text += line + '\n';
    }

    input.close();
    return text;
  }

  VEC_CH Scanner::readFileBinary(CR_FS_PATH path) {
    std::ifstream input(path, std::ios::binary);

    // file not found
    if (!input) return {};

    // get size
    input.seekg(0, std::ios::end);
    size_t size = input.tellg();

    // read content
    input.seekg(0);
    VEC_CH buffer(size);
    input.read(buffer.data(), size);

    input.close();
    return buffer;
  }
}}

#endif // __MINI_TOOLS__UTILS__SCANNER_CPP__