#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__STR_TOOLS_CPP__

#include <algorithm>
#include "str-tools.h"

namespace mini_tools {
namespace utils {

  void StrTools::changeStringCase(std::string &str, CR_BOL isUpper) {
    std::transform(
      str.begin(),
      str.end(),
      str.begin(),
      [&](unsigned char c) {
        if (isUpper) return std::toupper(c);
        else return std::tolower(c);
      }
    );
  }

  void StrTools::changeStringsCase(VEC_STR &vecStr, CR_BOL isUpper) {
    for (int i = 0; i < vecStr.size(); i++) {
      changeStringCase(vecStr.at(i), isUpper);
    }
  }

  void StrTools::changeStringToLowercase(std::string &str) {
    changeStringCase(str, false);
  }

  void StrTools::changeStringToUppercase(std::string &str) {
    changeStringCase(str, true);
  }

  std::string StrTools::getStringToLowercase(std::string str) {
    changeStringCase(str, false);
    return str;
  }

  std::string StrTools::getStringToUppercase(std::string str) {
    changeStringCase(str, true);
    return str;
  }

  void StrTools::stringsToLowercase(VEC_STR &vecStr) {
    changeStringsCase(vecStr, false);
  }

  void StrTools::stringsToUppercase(VEC_STR &vecStr) {
    changeStringsCase(vecStr, true);
  }

  std::string StrTools::uniteVector(
    CR_VEC_STR &vecStr,
    CR_STR separator
  ) {
    std::string text;

    for (const std::string &str : vecStr) {
      text += str + separator;
    }

    return text;
  }
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_CPP__