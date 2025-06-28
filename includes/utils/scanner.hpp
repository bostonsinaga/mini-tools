#ifndef __MINI_TOOLS__UTILS__SCANNER_HPP__
#define __MINI_TOOLS__UTILS__SCANNER_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  class Scanner final {
  public:
    Scanner() = delete;

    /** Text Separator Detectors */

    inline static VEC_CH separators_ch = {' ', ',', '\n'};
    inline static VEC_STR separators_str = {" ", ",", "\n"};

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

    static std::string readFileString(CR_FS_PATH path);

    /** Primitive Data Type Detectors */

    template <inspector::NUMBER T>
    T stringToNumber(CR_STR str);

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