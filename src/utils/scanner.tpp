#ifndef __MINI_TOOLS__UTILS__SCANNER_TPP__
#define __MINI_TOOLS__UTILS__SCANNER_TPP__

#include "utils/scanner.hpp"

namespace mini_tools {
namespace utils {

  /** Advanced Detectors */

  template <inspector::NUMBER T>
  T Scanner::stringToNumber(CR_STR numStr) {
    if constexpr (
      std::is_same_v<T, int> ||
      std::is_same_v<T, UI> ||
      std::is_same_v<T, SI> ||
      std::is_same_v<T, USI>
    ) {
      return std::stoi(numStr);
    }
    else if constexpr (std::is_same_v<T, float>) {
      return std::stof(numStr);
    }
    else if constexpr (std::is_same_v<T, double>) {
      return std::stod(numStr);
    }
    else if constexpr (std::is_same_v<T, LD>) {
      return std::stold(numStr);
    }
    else if constexpr (
      std::is_same_v<T, LI> ||
      std::is_same_v<T, ULI>
    ) {
      return std::stol(numStr);
    }
    else if constexpr (
      std::is_same_v<T, LLI> ||
      std::is_same_v<T, ULLI> ||
      std::is_same_v<T, size_t> ||
      std::is_same_v<T, time_t>
    ) {
      return std::stoll(numStr);
    }
  }

  template <inspector::NUMBER T>
  void Scanner::parseNumbers(
    CR_STR text,
    VEC<T> &vecHook
  ) {
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
          vecHook.push_back(Scanner::stringToNumber<T>(numStr));
          hasDecimalPoint = false;
          numStr = "";
        }
      }
    }
  }

  template <inspector::LETTER T>
  void Scanner::parseLetters(
    CR_STR text,
    VEC<T> &vecHook
  ) {
    bool separated = false;
    std::string chars;

    for (int i = 0; i < text.length(); i++) {

      if (separated && std::isalpha(text[i])) {
        separated = false;
      }

      if (!separated) {
        chars += text[i];

        if (Scanner::isSeparator(text, i)) {
          vecHook.push_back(chars);
          separated = true;
          chars = "";
        }
      }
    }
  }

  template <inspector::NUMBER T>
  VEC<T> Scanner::parseNumbers(CR_STR text) {
    VEC<T> numbers;
    Scanner::parseNumbers<T>(text, numbers);
    return numbers;
  }

  template <inspector::LETTER T>
  VEC<T> Scanner::parseLetters(CR_STR text) {
    VEC<T> letters;
    Scanner::parseLetters<T>(text, letters);
    return letters;
  }

  template <inspector::NUMBER T>
  VEC<T> Scanner::txtToNumbers(CR_FS_PATH filename) {

    return Scanner::parseNumbers<T>(
      Scanner::getFileString(filename)
    );
  }

  template <inspector::LETTER T>
  VEC<T> Scanner::txtToLetters(CR_FS_PATH filename) {

    return Scanner::parseLetters<T>(
      Scanner::getFileString(filename)
    );
  }
}}

#endif // __MINI_TOOLS__UTILS__SCANNER_TPP__