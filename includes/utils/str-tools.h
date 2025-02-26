#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_H__
#define __MINI_TOOLS__UTILS__STR_TOOLS_H__

#include "../types.h"

namespace mini_tools {
namespace utils {

  class StrTools {
  private:
    static void changeCase(char &ch, CR_BOL isUpper);

  public:
    static void changeToLowercase(char &ch);
    static void changeToUppercase(char &ch);
    static char getToLowercase(char ch);
    static char getToUppercase(char ch);

  private:
    static void changeCharCase(
      std::string &str,
      CR_LI index,
      CR_BOL isUpper
    );

  public:
    static void changeCharToLowercase(
      std::string &str,
      CR_LI index
    );

    static void changeCharToUppercase(
      std::string &str,
      CR_LI index
    );

    static std::string getCharToLowercase(
      std::string str,
      CR_LI index
    );

    static std::string getCharToUppercase(
      std::string str,
      CR_LI index
    );

  private:
    static void changeStringCase(std::string &str, CR_BOL isUpper);
    static void changeStringsCase(VEC_STR &vecStr, CR_BOL isUpper);

  public:
    static void changeStringToLowercase(std::string &str);
    static void changeStringToUppercase(std::string &str);

    static std::string getStringToLowercase(std::string str);
    static std::string getStringToUppercase(std::string str);

    static void changeStringsToLowercase(VEC_STR &vecStr);
    static void changeStringsToUppercase(VEC_STR &vecStr);

    static std::string uniteVector(
      CR_VEC_STR &vecStr,
      CR_STR separator = " ",
      CR_BOL separatedExceptLast = true
    );

    static bool isWhitespace(CR_CH ch) {
      return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
    }

    static bool isDigit(CR_CH ch) {
      return ch >= '0' && ch <= '9';
    }

    static bool isUppercaseLetter(CR_CH ch) {
      return ch >= 'A' && ch <= 'Z';
    }

    static bool isLowercaseLetter(CR_CH ch) {
      return ch >= 'a' && ch <= 'z';
    }

    static bool isLetter(CR_CH ch) {
      return isUppercaseLetter(ch) || isLowercaseLetter(ch);
    }
  };
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_H__