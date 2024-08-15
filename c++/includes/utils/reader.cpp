#ifndef __MINI_TOOLS__UTILS__READER_CPP__
#define __MINI_TOOLS__UTILS__READER_CPP__

namespace mini_tools {
namespace utils {

  template <typename T>
  constexpr bool Scanner<T>::checkNumberType() {

    if constexpr (!CheckType::isNumber<T>()) {

      constexpr bool checkNumberType_error = false;
      static_assert(checkNumberType_error, "only for numbers");
      return false;
    }
    else return true;
  }

  template <typename T>
  constexpr bool Scanner<T>::checkLetterType() {

    if constexpr (!CheckType::isLetter<T>()) {

      constexpr bool checkLetterType_error = false;
      static_assert(checkLetterType_error, "only for letters");
      return false;
    }
    else return true;
  }

  template <typename T>
  void Scanner<T>::parseNumbers(
    CR_STR text,
    std::vector<T> &vecHook
  ) {
    if constexpr (Scanner<T>::checkNumberType()) {
      bool separated = false;
      std::string numStr;

      for (int i = 0; i < text.length(); i++) {
        
        if (separated && std::isdigit(text[i])) {
          separated = false;
        }

        if (!separated) {
          if (std::isdigit(text[i])) {
            numStr += text[i];
          }
          else if (Reader::isSeparator(text, i)) {

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
  }

  template <typename T>
  void Scanner<T>::parseLetters(
    CR_STR text,
    std::vector<T> &vecHook
  ) {
    if constexpr (Scanner<T>::checkLetterType()) {
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
  }

  template <typename T>
  std::vector<T> Scanner<T>::parseNumbers(CR_STR text) {

    if constexpr (Scanner<T>::checkNumberType()) {
      std::vector<T> numbers;
      Scanner<T>::parseNumbers(text, numbers);
      return numbers;
    }
  }

  template <typename T>
  std::vector<T> Scanner<T>::parseLetters(CR_STR text) {

    if constexpr (Scanner<T>::checkLetterType()) {
      std::vector<T> letters;
      Scanner<T>::parseLetters(text, letters);
      return letters;
    }
  }

  template <typename T>
  std::vector<T> Scanner<T>::txtToNumbers(CR_STR filename) {

    if constexpr (Scanner<T>::checkNumberType()) {
      std::string text;
      Reader::getFrom(filename, text);
      return parseNumbers(text);
    }
  }

  template <typename T>
  std::vector<T> Scanner<T>::txtToLetters(CR_STR filename) {

    if constexpr (Scanner<T>::checkLetterType()) {
      std::string text;
      Reader::getFrom(filename, text);
      return parseLetters(text);
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__READER_CPP__