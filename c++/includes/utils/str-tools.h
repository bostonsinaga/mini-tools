#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_H__
#define __MINI_TOOLS__UTILS__STR_TOOLS_H__

#include "../types.h"

namespace mini_tools {
namespace utils {

  class StrTools {
  private:
    static void changeStringCase(std::string &str, bool isUpper);
    static void changeStringsCase(std::vector<std::string> *vecStr, bool isUpper);

  public:
    static void changeStringToLowercase(std::string &str);
    static void changeStringToUppercase(std::string &str);

    static std::string getStringToLowercase(std::string str);
    static std::string getStringToUppercase(std::string str);

    static void stringsToLowercase(VEC_STR *vecStr);
    static void stringsToUppercase(VEC_STR *vecStr);
  };
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_H__