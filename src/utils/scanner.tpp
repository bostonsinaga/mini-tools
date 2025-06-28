#ifndef __MINI_TOOLS__UTILS__SCANNER_TPP__
#define __MINI_TOOLS__UTILS__SCANNER_TPP__

#include "utils/scanner.hpp"

namespace mini_tools {
namespace utils {

  /** Primitive Data Type Detectors */

  template <inspector::NUMBER T>
  T Scanner::stringToNumber(CR_STR str) {

    // select all available number conversion types
    try {
      if constexpr (std::is_same_v<T, int>) {
        return std::stoi(str);
      }
      else if constexpr (std::is_same_v<T, long>) {
        return std::stol(str);
      }
      else if constexpr (std::is_same_v<T, LLI>) {
        return std::stoll(str);
      }
      else if constexpr (std::is_same_v<T, ULI>) {
        return std::stoul(str);
      }
      else if constexpr (std::is_same_v<T, ULLI>) {
        return std::stoull(str);
      }
      else if constexpr (std::is_same_v<T, float>) {
        return std::stof(str);
      }
      else if constexpr (std::is_same_v<T, double>) {
        return std::stod(str);
      }
      else if constexpr (std::is_same_v<T, LD>) {
        return std::stold(str);
      }
      else return std::stoi(str);
    }
    catch (...) {}

    /**
     * The 'str' is empty or 'str' does not contain numbers
     * or does not start with a number or decimal point.
     */
    return T();
  }

  template <inspector::NUMBER T>
  VEC<T> Scanner::parseNumbers(CR_STR text) {

    VEC<T> numVec;
    std::string numStr;

    bool separated = false,
      hasDecimalPoint = false,
      skip = false;

    for (int i = 0; i < text.length(); i++) {

      if (separated && std::isdigit(text[i])) {
        separated = false;
      }

      if (!separated) {
        bool isDecimalPoint = numStr.length() > 0 && text[i] == '.';

        if (std::isdigit(text[i]) || (
          !hasDecimalPoint && isDecimalPoint
        )) {
          numStr += text[i];
          if (isDecimalPoint) hasDecimalPoint = true;

          if (i == text.length() - 1) skip = false;
          else skip = true;
        }
        else skip = false;

        if (!skip &&
          Scanner::isSeparator(text, i) &&
          numStr.length() > 0
        ) {
          numVec.push_back(StrTools::stringToNumber<T>(numStr));
          hasDecimalPoint = false;
          numStr = "";
        }
      }
    }

    return numVec;
  }

  template <inspector::LETTER T>
  VEC<T> Scanner::parseLetters(CR_STR text) {

    VEC<T> wordVec;
    bool separated = false;
    std::string chars;

    for (int i = 0; i < text.length(); i++) {

      if (separated && std::isalpha(text[i])) {
        separated = false;
      }

      if (!separated) {
        chars += text[i];

        if (Scanner::isSeparator(text, i)) {
          wordVec.push_back(chars);
          separated = true;
          chars = "";
        }
      }
    }

    return wordVec;
  }

  template <inspector::NUMBER T>
  VEC<T> Scanner::txtToNumbers(CR_FS_PATH filename) {

    return Scanner::parseNumbers<T>(
      Scanner::readFileString(filename)
    );
  }

  template <inspector::LETTER T>
  VEC<T> Scanner::txtToLetters(CR_FS_PATH filename) {

    return Scanner::parseLetters<T>(
      Scanner::readFileString(filename)
    );
  }
}}

#endif // __MINI_TOOLS__UTILS__SCANNER_TPP__