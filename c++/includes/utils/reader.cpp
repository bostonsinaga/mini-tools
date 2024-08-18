#ifndef __MINI_TOOLS__UTILS__READER_CPP__
#define __MINI_TOOLS__UTILS__READER_CPP__

namespace mini_tools {
namespace utils {

  template <typename T>
  void Scanner<T>::parseNumbers(
    CR_STR text,
    VEC<T> &vecHook
  ) {
    if constexpr (CheckType::isNumber<T>()) {
      bool separated = false, skip = false;
      std::string numStr;

      for (int i = 0; i < text.length(); i++) {
        
        if (separated && std::isdigit(text[i])) {
          separated = false;
        }

        if (!separated) {

          if (std::isdigit(text[i])) {
            numStr += text[i];
            if (i == text.length() - 1) skip = false;
            else skip = true;
          }
          else skip = false;

          if (!skip &&
            Reader::isSeparator(text, i) &&
            numStr.length() > 0
          ) {
            if constexpr (std::is_same<T, float>::value) {
              vecHook.push_back(std::stof(numStr));
            }
            else if constexpr (std::is_same<T, double>::value) {
              vecHook.push_back(std::stod(numStr));
            }
            else if constexpr (std::is_same<T, LD>::value) {
              vecHook.push_back(std::stold(numStr));
            }
            else vecHook.push_back(std::stoi(numStr));

            numStr = "";
          }
        }
      }
    }
    else {
      constexpr bool ERROR = false;
      static_assert(ERROR, "'parseNumbers(CR_STR, VEC<T>&)' template type");
    }
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
    else {
      constexpr bool ERROR = false;
      static_assert(ERROR, "'parseLetters(CR_STR, VEC<T>&)' template type");
    }
  }

  template <typename T>
  VEC<T> Scanner<T>::parseNumbers(CR_STR text) {

    if constexpr (CheckType::isNumber<T>()) {
      VEC<T> numbers;
      Scanner<T>::parseNumbers(text, numbers);
      return numbers;
    }
    else {
      constexpr bool ERROR = false;
      static_assert(ERROR, "'parseNumbers(CR_STR)' template type");
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
      constexpr bool ERROR = false;
      static_assert(ERROR, "'parseLetters(CR_STR)' template type");
    }
  }

  template <typename T>
  VEC<T> Scanner<T>::txtToNumbers(CR_STR filename) {

    if constexpr (CheckType::isNumber<T>()) {
      std::string text;
      Reader::getFrom(filename, text);
      return Scanner<T>::parseNumbers(text);
    }
    else {
      constexpr bool ERROR = false;
      static_assert(ERROR, "'txtToNumbers(CR_STR)' template type");
    }
  }

  template <typename T>
  VEC<T> Scanner<T>::txtToLetters(CR_STR filename) {

    if constexpr (CheckType::isLetter<T>()) {
      std::string text;
      Reader::getFrom(filename, text);
      return Scanner<T>::parseLetters(text);
    }
    else {
      constexpr bool ERROR = false;
      static_assert(ERROR, "'txtToLetters(CR_STR)' template type");
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__READER_CPP__