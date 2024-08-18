#ifndef __MINI_TOOLS__UTILS__READER_CPP__
#define __MINI_TOOLS__UTILS__READER_CPP__

#include <fstream>

namespace mini_tools {
namespace utils {

  bool Reader::isSeparator(CR_CHR ch) {
    if (ch == ' ' || ch == ',' || ch == '\n') return true;
    return false;
  }

  bool Reader::isSeparator(CR_STR text, CR_INT i) {
    if (i >= 0 && i < text.length()) {
      if (isSeparator(text[i]) || i == text.length() - 1) {
        return true;
      }
      return false;
    }
    return false;
  }

  void Reader::getFile(
    CR_STR name,
    std::string &textHook
  ) {
    std::string line;
    std::ifstream reader(name);
    while (std::getline(reader, line)) { textHook += line; }
    reader.close();
  }

  template <typename T>
  void Reader::parseNumbers(
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
            hasDecimalPoint = false;
          }
        }
      }
    }
    else static_assert(0, "template type");
  }

  template <typename T>
  void Reader::parseLetters(
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
  VEC<T> Reader::parseNumbers(CR_STR text) {

    if constexpr (CheckType::isNumber<T>()) {
      VEC<T> numbers;
      Reader::parseNumbers<T>(text, numbers);
      return numbers;
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }

  template <typename T>
  VEC<T> Reader::parseLetters(CR_STR text) {

    if constexpr (CheckType::isLetter<T>()) {
      VEC<T> letters;
      Reader::parseLetters<T>(text, letters);
      return letters;
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }

  template <typename T>
  VEC<T> Reader::txtToNumbers(CR_STR filename) {

    if constexpr (CheckType::isNumber<T>()) {
      std::string text;
      Reader::getFile(filename, text);
      return Reader::parseNumbers<T>(text);
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }

  template <typename T>
  VEC<T> Reader::txtToLetters(CR_STR filename) {

    if constexpr (CheckType::isLetter<T>()) {
      std::string text;
      Reader::getFile(filename, text);
      return Reader::parseLetters<T>(text);
    }
    else {
      static_assert(0, "template type");
      return {};
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__READER_CPP__