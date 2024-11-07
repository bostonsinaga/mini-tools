#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__STR_TOOLS_CPP__

#include <algorithm>
#include "str-tools.h"

namespace mini_tools {
namespace utils {

  void StrTools::changeCase(char &ch, CR_BOL isUpper) {
    if (isUpper) {
      ch = std::toupper(ch);
    }
    else ch = std::tolower(ch);
  }

  void StrTools::changeToLowercase(char &ch) {
    changeCase(ch, false);
  }

  void StrTools::changeToUppercase(char &ch) {
    changeCase(ch, true);
  }

  char StrTools::getToLowercase(char ch) {
    changeCase(ch, false);
    return ch;
  }

  char StrTools::getToUppercase(char ch) {
    changeCase(ch, true);
    return ch;
  }

  void StrTools::changeCharCase(
    std::string &str,
    CR_LI index,
    CR_BOL isUpper
  ) {
    if (index >= 0 && index < str.length()) {
      changeCase(str[index], isUpper);
    }
  }

  void StrTools::changeCharToLowercase(
    std::string &str,
    CR_LI index
  ) {
    changeCharCase(str, index, false);
  }

  void StrTools::changeCharToUppercase(
    std::string &str,
    CR_LI index
  ) {
    changeCharCase(str, index, true);
  }

  std::string StrTools::getCharToLowercase(
    std::string str,
    CR_LI index
  ) {
    changeCharCase(str, index, false);
    return str;
  }

  std::string StrTools::getCharToUppercase(
    std::string str,
    CR_LI index
  ) {
    changeCharCase(str, index, true);
    return str;
  }

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

  void StrTools::changeStringsToLowercase(VEC_STR &vecStr) {
    changeStringsCase(vecStr, false);
  }

  void StrTools::changeStringsToUppercase(VEC_STR &vecStr) {
    changeStringsCase(vecStr, true);
  }

  std::string StrTools::uniteVector(
    CR_VEC_STR &vecStr,
    CR_STR separator,
    CR_BOL separatedExceptLast
  ) {
    std::string text;

    for (const std::string &str : vecStr) {
      text += str + separator;
    }

    if (separatedExceptLast &&
      !(text.empty() || separator.empty())
    ) { text.pop_back(); }

    return text;
  }

  bool StrTools::isWhitespace(CR_CH ch) {
    if (ch == ' ' || ch == '\t') {
      return true;
    }
    return false;
  }

  bool StrTools::isSpaceLine(CR_CH ch) {
    if (isWhitespace(ch) || ch == '\n') {
      return true;
    }
    return false;
  }
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_CPP__