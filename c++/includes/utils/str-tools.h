#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_H__
#define __MINI_TOOLS__UTILS__STR_TOOLS_H__

#include "../types.h"

namespace mini_tools {
namespace utils {

  class StrTools {
  private:
    static void changeStringCase(std::string &str, CR_BOL isUpper);
    static void changeStringsCase(VEC_STR &vecStr, CR_BOL isUpper);

  public:
    static void changeStringToLowercase(std::string &str);
    static void changeStringToUppercase(std::string &str);

    static std::string getStringToLowercase(std::string str);
    static std::string getStringToUppercase(std::string str);

    static void stringsToLowercase(VEC_STR &vecStr);
    static void stringsToUppercase(VEC_STR &vecStr);

    static std::string uniteVector(
      CR_VEC_STR &vecStr,
      CR_STR separator = " ",
      CR_BOL separatedExceptLast = true
    );
  };
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_H__