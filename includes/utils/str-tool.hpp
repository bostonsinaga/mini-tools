#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_HPP__
#define __MINI_TOOLS__UTILS__STR_TOOLS_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  class StrTools final {
  private:
    static void modifyCase(char &ch, CR_BOL isUpper);

  public:
    StrTools() = delete;

    static void modifyToLowercase(char &ch);
    static void modifyToUppercase(char &ch);
    static char copyToLowercase(char ch);
    static char copyToUppercase(char ch);

  private:
    static void modifyCharCase(
      std::string &str,
      CR_LI index,
      CR_BOL isUpper
    );

  public:
    static void modifyCharToLowercase(
      std::string &str,
      CR_LI index
    );

    static void modifyCharToUppercase(
      std::string &str,
      CR_LI index
    );

    static std::string copyCharToLowercase(
      std::string str,
      CR_LI index
    );

    static std::string copyCharToUppercase(
      std::string str,
      CR_LI index
    );

  private:
    static void modifyStringCase(std::string &str, CR_BOL isUpper);
    static void modifyStringsCase(VEC_STR &vecStr, CR_BOL isUpper);

  public:
    static void modifyStringToLowercase(std::string &str);
    static void modifyStringToUppercase(std::string &str);

    static std::string copyStringToLowercase(std::string str);
    static std::string copyStringToUppercase(std::string str);

    static void modifyStringsToLowercase(VEC_STR &vecStr);
    static void modifyStringsToUppercase(VEC_STR &vecStr);

    static std::string joinVector(
      CR_VEC_STR &vecStr,
      CR_STR separator = " ",
      CR_BOL separatedExceptLast = true
    );

    /**
     * Find the first character index other than
     * space or newline from left and right.
     */
    static void findSpaceBoundaryIndex(
      std::string &text,
      int &forwardSpaceBoundaryIndex,
      int &reverseSpaceBoundaryIndex
    );

    /**
     * Change non-capital letters after dots
     * and reduce excess spaces inside.
     */
    static void tidyUp(
      std::string &text,
      CR_BOL noNewline = false,
      CR_INT forwardSpaceBoundaryIndex = -1,
      CR_INT reverseSpaceBoundaryIndex = -1
    );

    /**
     * Remove spaces from the left
     * and right sides of a string.
     */
    static std::string trim(CR_STR text);

    /** Character Detectors */

    static bool isWhitespace(CR_CH ch);
    static bool isWhitespaces(CR_STR str);
    static bool isUppercaseLetter(CR_CH ch);
    static bool isLowercaseLetter(CR_CH ch);
    static bool isLetter(CR_CH ch);

    /** Number Detectors */

    static bool isDigit(CR_CH ch);
    static bool isInteger(CR_STR str);

    static bool isFloatingPoint(
      CR_STR str, CR_CH decPtSign = '.'
    );

    /**
     * The 'argc' is expected to have a value that corresponds
     * to the actual number of 'argv' or both are parameters of the main function.
     */
    static VEC_STR argvToStringVector(
      CR_INT argc, char *argv[]
    );
  };
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_HPP__