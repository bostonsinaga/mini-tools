#ifndef __MINI_TOOLS__UTILS__SCANNER_H__
#define __MINI_TOOLS__UTILS__SCANNER_H__

namespace mini_tools {
namespace utils {

  typedef const fs::path& CR_PATH;

  class Scanner {
  public:
    static VEC_CH separators_ch;
    static VEC_STR separators_str;

    static bool isSeparator(CR_CH ch);
    static bool isSeparator(CR_STR str);
    static bool isSeparator(CR_STR text, CR_INT idx);
    static bool isSeparator(CR_VEC_STR textVec, CR_INT idx);

    static bool isFileExist(CR_PATH path);
    static bool isDirectoryExist(CR_PATH path);
    static bool createNotExistFile(CR_PATH path);
    static bool createNotExistDirectory(CR_STR path);

    static fs::path findPath(
      fs::path &path,
      CR_BOL toFile,
      CR_BOL upward
    );

    static fs::path findFile(
      fs::path path, CR_BOL upward
    ) {
      return Scanner::findPath(path, true, upward);
    }

    static fs::path findDirectory(
      fs::path path, CR_BOL upward
    ) {
      return Scanner::findPath(path, false, upward);
    }

    static void getFile(
      CR_STR name,
      std::string &textHook
    );

    template <inspector::NUMBER T>
    static T stringToNumber(CR_STR numStr);

    template <inspector::NUMBER T>
    static void parseNumbers(CR_STR text, VEC<T> &vecHook);

    template <inspector::LETTER T>
    static void parseLetters(CR_STR text, VEC<T> &vecHook);

    template <inspector::NUMBER T>
    static VEC<T> parseNumbers(CR_STR text);

    template <inspector::LETTER T>
    static VEC<T> parseLetters(CR_STR text);

    template <inspector::NUMBER T>
    static VEC<T> txtToNumbers(CR_STR filename);

    template <inspector::LETTER T>
    static VEC<T> txtToLetters(CR_STR filename);
  };
}}

#include "utils/scanner.tpp"
#endif // __MINI_TOOLS__UTILS__SCANNER_H__