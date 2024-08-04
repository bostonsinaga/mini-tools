#ifndef __MINI_TOOLS__UTILS__READER_CPP__
#define __MINI_TOOLS__UTILS__READER_CPP__

namespace mini_tools {
namespace utils {

  template <typename T>
  std::vector<T> Scanner<T>::txtToNumbers(std::string filename) {

    if constexpr (!CheckType::isNumber<T>()) {
      constexpr bool txtToNumbers_template_error = false;
      static_assert(txtToNumbers_template_error, "only for numbers");
    }
    else {
      std::string text;
      Reader::getFrom(filename, text);

      /** Convert to numbers */

      std::vector<T> numbers;
      std::string numStr;

      for (int i = 0; i < text.length(); i++) {
        if (std::isdigit(text[i])) {
          numStr += text[i];
        }
        else if (Reader::isSeparator(text, i)) {
          numbers.push_back(std::stoi(numStr));
          numStr = "";
        }
      }

      return numbers;
    }
  }

  template <typename T>
  std::vector<T> Scanner<T>::txtToLetters(std::string filename) {

    if constexpr (!CheckType::isLetter<T>()) {
      constexpr bool txtToLetters_template_error = false;
      static_assert(txtToLetters_template_error, "only for letters");
    }
    else {
      std::string text;
      Reader::getFrom(filename, text);

      /** Convert to letters */

      std::vector<T> letters;
      std::string chars;

      for (int i = 0; i < text.length(); i++) {
        chars += text[i];

        if (Reader::isSeparator(text, i)) {
          letters.push_back(chars);
          chars = "";
        }
      }

      return letters;
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__READER_CPP__