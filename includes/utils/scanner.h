#ifndef __MINI_TOOLS__UTILS__SCANNER_H__
#define __MINI_TOOLS__UTILS__SCANNER_H__

namespace mini_tools {
namespace utils {

  class Scanner {
  public:
    static VEC_CH separators_ch;
    static VEC_STR separators_str;

    static bool isSeparator(CR_CH ch);
    static bool isSeparator(CR_STR str);
    static bool isSeparator(CR_STR text, CR_INT idx);
    static bool isSeparator(CR_VEC_STR textVec, CR_INT idx);

    static void getFile(
      CR_STR name,
      std::string &textHook
    );

    template <typename T>
    static T stringToNumber(CR_STR numStr);

    template <typename T>
    static void parseNumbers(CR_STR text, VEC<T> &vecHook);

    template <typename T>
    static void parseLetters(CR_STR text, VEC<T> &vecHook);

    template <typename T>
    static VEC<T> parseNumbers(CR_STR text);

    template <typename T>
    static VEC<T> parseLetters(CR_STR text);

    template <typename T>
    static VEC<T> txtToNumbers(CR_STR filename);

    template <typename T>
    static VEC<T> txtToLetters(CR_STR filename);
  };
}}

#include "utils/scanner.tpp"
#endif // __MINI_TOOLS__UTILS__SCANNER_H__