#ifndef __MINI_TOOLS__UTILS__SCANNER_H__
#define __MINI_TOOLS__UTILS__SCANNER_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class Scanner {
  public:
    static VEC_CH separators_ch = {' ', ',', '\n'};
    static VEC_STR separators_str = {" ", ",", "\n"};

    static bool isSeparator(CR_CH ch);
    static bool isSeparator(CR_STR str);
    static bool isSeparator(CR_STR text, CR_INT idx);
    static bool isSeparator(CR_VEC_STR textVec, CR_INT idx);

    static void getFile(
      CR_STR name,
      std::string &textHook
    );

    static T stringToNumber(CR_STR numStr);
    static void parseNumbers(CR_STR text, VEC<T> &vecHook);
    static void parseLetters(CR_STR text, VEC<T> &vecHook);
    static VEC<T> parseNumbers(CR_STR text);
    static VEC<T> parseLetters(CR_STR text);
    static VEC<T> txtToNumbers(CR_STR filename);
    static VEC<T> txtToLetters(CR_STR filename);
  };
}}

#include "utils/scanner.tpp"
#endif // __MINI_TOOLS__UTILS__SCANNER_H__