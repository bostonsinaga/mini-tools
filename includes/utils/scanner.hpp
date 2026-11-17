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

    /** File Readers */

    static std::string readFileString(CR_FS_PATH filename);
    static VEC_CH readFileBinary(CR_FS_PATH filename);

    /** Primitive Data Type Parsers */

    template <NUMBER T>
    static T stringToNumber(CR_STR str);

    template <NUMBER T>
    static VEC_STR numbersToStrings(CR_VEC<T> numbers);

    template <NUMBER T>
    static VEC<T> parseNumbers(CR_STR text);

    template <STRING T>
    static VEC<T> parseWords(CR_STR text);

    /** Read TXT File */

    template <NUMBER T>
    static VEC<T> txtToNumbers(CR_FS_PATH filename);

    template <STRING T>
    static VEC<T> txtToWords(CR_FS_PATH filename);
  };
}}

#include "utils/scanner.tpp"
#endif // __MINI_TOOLS__UTILS__SCANNER_HPP__