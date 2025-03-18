#ifndef __MINI_TOOLS__UTILS__SCANNER_TPP__
#define __MINI_TOOLS__UTILS__SCANNER_TPP__

namespace mini_tools {
namespace utils {

  template <typename T>
  T Scanner<T>::stringToNumber(CR_STR numStr) {
    if constexpr (
      std::is_same<T, int>::value ||
      std::is_same<T, UI>::value ||
      std::is_same<T, SI>::value ||
      std::is_same<T, USI>::value
    ) {
      return std::stoi(numStr);
    }
    else if constexpr (std::is_same<T, float>::value) {
      return std::stof(numStr);
    }
    else if constexpr (std::is_same<T, double>::value) {
      return std::stod(numStr);
    }
    else if constexpr (std::is_same<T, LD>::value) {
      return std::stold(numStr);
    }
    else if constexpr (
      std::is_same<T, LI>::value ||
      std::is_same<T, ULI>::value
    ) {
      return std::stol(numStr);
    }
    else if constexpr (
      std::is_same<T, LLI>::value ||
      std::is_same<T, ULLI>::value ||
      std::is_same<T, size_t>::value ||
      std::is_same<T, time_t>::value
    ) {
      return std::stoll(numStr);
    }
  }

  template <typename T>
  void Scanner<T>::parseNumbers(
    CR_STR text,
    VEC<T> &vecHook
  ) {
    if constexpr (CheckType::isNumber<T>()) {
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
            Reader::isSeparator(text, i) &&
            numStr.length() > 0
          ) {
            vecHook.push_back(Scanner<T>::stringToNumber(numStr));
            hasDecimalPoint = false;
            numStr = "";
          }
        }
      }
    }
    else static_assert(0, "template type");
  }

  template <typename T>
  void Scanner<T>::parseLetters(
    CR_STR text,
    VEC<T> &vecHook
  ) {
    if constexpr (CheckType::isLetter<T>()) {
      bool separated = false;
      std::string chars;

      for (int i = 0; i < text.length(); i++) {

        if (separated && std::isalpha(text[i])) {
          separated = false;
        }

        if (!separated) {
          chars += text[i];

          if (Reader::isSeparator(text, i)) {
            vecHook.push_back(chars);
            separated = true;
            chars = "";
          }
        }
      }
    }
    else static_assert(0, "template type");
  }

  template <typename T>
  VEC<T> Scanner<T>::parseNumbers(CR_STR text) {

    if constexpr (CheckType::isNumber<T>()) {
      VEC<T> numbers;
      Scanner<T>::parseNumbers(text, numbers);
      return numbers;
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }

  template <typename T>
  VEC<T> Scanner<T>::parseLetters(CR_STR text) {

    if constexpr (CheckType::isLetter<T>()) {
      VEC<T> letters;
      Scanner<T>::parseLetters(text, letters);
      return letters;
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }

  template <typename T>
  VEC<T> Scanner<T>::txtToNumbers(CR_STR filename) {

    if constexpr (CheckType::isNumber<T>()) {
      std::string text;
      Reader::getFile(filename, text);
      return Scanner<T>::parseNumbers(text);
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }

  template <typename T>
  VEC<T> Scanner<T>::txtToLetters(CR_STR filename) {

    if constexpr (CheckType::isLetter<T>()) {
      std::string text;
      Reader::getFile(filename, text);
      return Scanner<T>::parseLetters(text);
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__SCANNER_TPP__