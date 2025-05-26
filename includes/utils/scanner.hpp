#ifndef __MINI_TOOLS__UTILS__SCANNER_HPP__
#define __MINI_TOOLS__UTILS__SCANNER_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  class Scanner final {
  public:
    Scanner() = delete;

    /** Simple Detectors */

    static VEC_CH separators_ch;
    static VEC_STR separators_str;

    static bool isSeparator(CR_CH ch);
    static bool isSeparator(CR_STR str);
    static bool isSeparator(CR_STR text, CR_INT idx);
    static bool isSeparator(CR_VEC_STR textVec, CR_INT idx);

    /** Text File or Directory Readers */

    static bool isFileExist(CR_FS_PATH path);
    static bool isDirectoryExist(CR_FS_PATH path);
    static bool createNotExistFile(CR_FS_PATH path);
    static bool createNotExistDirectory(CR_FS_PATH path);

    static FS_PATH findPath(
      FS_PATH &path,
      CR_BOL toFile,
      CR_BOL upward
    );

    static FS_PATH findFile(
      FS_PATH path,
      CR_BOL upward
    ) {
      return Scanner::findPath(path, true, upward);
    }

    static FS_PATH findDirectory(
      FS_PATH path,
      CR_BOL upward
    ) {
      return Scanner::findPath(path, false, upward);
    }

    static void getFile(
      CR_FS_PATH path,
      std::string &textHook
    );

    /** Advanced Detectors */

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
    static VEC<T> txtToNumbers(CR_FS_PATH filename);

    template <inspector::LETTER T>
    static VEC<T> txtToLetters(CR_FS_PATH filename);
  };
}}

#include "utils/scanner.tpp"
#endif // __MINI_TOOLS__UTILS__SCANNER_HPP__