#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__STR_TOOLS_CPP__

#include "utils/str-tools.hpp"

namespace mini_tools {
namespace utils {

  void StrTools::modifyCase(char &ch, CR_BOL isUpper) {
    if (isUpper) {
      ch = std::toupper(ch);
    }
    else ch = std::tolower(ch);
  }

  void StrTools::modifyToLowercase(char &ch) {
    modifyCase(ch, false);
  }

  void StrTools::modifyToUppercase(char &ch) {
    modifyCase(ch, true);
  }

  char StrTools::copyToLowercase(char ch) {
    modifyCase(ch, false);
    return ch;
  }

  char StrTools::copyToUppercase(char ch) {
    modifyCase(ch, true);
    return ch;
  }

  void StrTools::modifyCharCase(
    std::string &str,
    CR_LI index,
    CR_BOL isUpper
  ) {
    if (index >= 0 && index < str.length()) {
      modifyCase(str[index], isUpper);
    }
  }

  void StrTools::modifyCharToLowercase(
    std::string &str,
    CR_LI index
  ) {
    modifyCharCase(str, index, false);
  }

  void StrTools::modifyCharToUppercase(
    std::string &str,
    CR_LI index
  ) {
    modifyCharCase(str, index, true);
  }

  std::string StrTools::copyCharToLowercase(
    std::string str,
    CR_LI index
  ) {
    modifyCharCase(str, index, false);
    return str;
  }

  std::string StrTools::copyCharToUppercase(
    std::string str,
    CR_LI index
  ) {
    modifyCharCase(str, index, true);
    return str;
  }

  void StrTools::modifyStringCase(std::string &str, CR_BOL isUpper) {
    std::transform(
      str.begin(), str.end(), str.begin(),
      [&](unsigned char c) {
        if (isUpper) return std::toupper(c);
        else return std::tolower(c);
      }
    );
  }

  void StrTools::modifyStringsCase(VEC_STR &vecStr, CR_BOL isUpper) {
    for (int i = 0; i < vecStr.size(); i++) {
      modifyStringCase(vecStr.at(i), isUpper);
    }
  }

  void StrTools::modifyStringToLowercase(std::string &str) {
    modifyStringCase(str, false);
  }

  void StrTools::modifyStringToUppercase(std::string &str) {
    modifyStringCase(str, true);
  }

  std::string StrTools::copyStringToLowercase(std::string str) {
    modifyStringCase(str, false);
    return str;
  }

  std::string StrTools::copyStringToUppercase(std::string str) {
    modifyStringCase(str, true);
    return str;
  }

  void StrTools::modifyStringsToLowercase(VEC_STR &vecStr) {
    modifyStringsCase(vecStr, false);
  }

  void StrTools::modifyStringsToUppercase(VEC_STR &vecStr) {
    modifyStringsCase(vecStr, true);
  }

  std::string StrTools::joinVector(
    CR_VEC_STR &vecStr,
    CR_STR separator,
    CR_BOL separatedExceptLast
  ) {
    std::string text;

    for (const std::string &str : vecStr) {
      text += str + separator;
    }

    if (separatedExceptLast &&
      !(text.empty() || separator.empty())
    ) { text.pop_back(); }

    return text;
  }

  void StrTools::findSpaceBoundaryIndex(
    std::string &text,
    int &forwardSpaceBoundaryIndex,
    int &reverseSpaceBoundaryIndex
  ) {
    if (!text.empty()) {

      // forward
      for (forwardSpaceBoundaryIndex = 0;
        forwardSpaceBoundaryIndex < text.length();
        forwardSpaceBoundaryIndex++
      ) {
        if (!isWhitespace(text[forwardSpaceBoundaryIndex])) {
          forwardSpaceBoundaryIndex--;
          break;
        }
      }

      // reverse
      for (reverseSpaceBoundaryIndex = text.length() - 1;
        reverseSpaceBoundaryIndex >= 0;
        reverseSpaceBoundaryIndex--
      ) {
        if (!isWhitespace(text[reverseSpaceBoundaryIndex])) {
          reverseSpaceBoundaryIndex++;
          break;
        }
      }
    }
  }

  void StrTools::tidyUp(
    std::string &text,
    CR_BOL noNewline,
    CR_INT forwardSpaceBoundaryIndex,
    CR_INT reverseSpaceBoundaryIndex
  ) {
    // start with capital letter
    for (int i = forwardSpaceBoundaryIndex < 0 ?
      0 : forwardSpaceBoundaryIndex;
      i < text.length(); i++
    ) {
      if (!isWhitespace(text[i])) {
        modifyCharToUppercase(text, i);
        break;
      }
    }

    // end with period
    for (int i = reverseSpaceBoundaryIndex >= text.length() ?
      text.length() - 1 : reverseSpaceBoundaryIndex;
      i >= 0; i--
    ) {
      if (!isWhitespace(text[i])) {
        text.insert(i, ".");
        break;
      }
    }

    /** Inner Tidying */

    enum recently {character, space, newline};
    PAIR<recently> recent {character, character};
    size_t sliceIndex = 0, sliceSize = 0;

    bool mayNeedSpace = false,
      willCapitalized = false;

    for (int i = 0; i < text.length(); i++) {
      // dot detected
      if (text[i] == '.') {
        mayNeedSpace = true;
        willCapitalized = true;
        recent.second = recent.first;
        recent.first = character;
      }
      // change to uppercase
      else if (isLetter(text[i])) {
        recent.second = recent.first;
        recent.first = character;

        // add space between dot and letter
        if (mayNeedSpace) {
          mayNeedSpace = false;
          text.insert(text.begin() + i, ' ');
          i++;
        }

        // letter after the dot changed to uppercase
        if (willCapitalized) {
          modifyToUppercase(text[i]);
          willCapitalized = false;
        }
      }
      // numbers ignored
      else if (isDigit(text[i])) {
        willCapitalized = false;
        recent.second = recent.first;
        recent.first = character;
      }
      // replace tab to space
      else if (text[i] == '\t') {
        text[i] = ' ';
        recent.second = recent.first;
        recent.first = space;
      }
      // replace carriage return to newline
      else if (text[i] == '\r') {
        if (noNewline) {
          text[i] = ' ';
          recent.second = recent.first;
          recent.first = space;
        }
        else {
          text[i] = '\n';
          recent.second = recent.first;
          recent.first = newline;
        }
      }
      // space detected
      else if (text[i] == ' ') {
        recent.second = recent.first;
        recent.first = space;
      }
      // newline detected
      else if (text[i] == '\n') {
        if (noNewline) {
          text[i] = ' ';
          recent.second = recent.first;
          recent.first = space;
        }
        else {
          recent.second = recent.first;
          recent.first = newline;
        }
      }

      // non-consecutive whitespace characters detected
      if (recent.first != character || recent.second != character) {
        if (recent.first != recent.second) {

          // remove the excess
          if (sliceSize > 0) {
            text = text.substr(0, sliceIndex + 1)
              + text.substr(sliceIndex + sliceSize + 1);
          }

          sliceIndex = i;
          sliceSize = 0;
        }
        else sliceSize++;
      }
    }
  }

  std::string StrTools::trim(CR_STR text) {
    size_t i = 0, index = 0, length = 0;

    for (; i < text.length(); i++) {
      if (isWhitespace(text[i])) {
        index++;
      }
      else break;
    }

    for (int j = i; j < text.length(); j++) {
      if (isWhitespace(text[j])) {
        break;
      }
      else length++;
    }

    return text.substr(index, length);
  }

  /** Character Detectors */

  bool StrTools::isWhitespace(CR_CH ch) {
    return ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n';
  }

  bool StrTools::isWhitespaces(CR_STR str) {
    for (CR_CH ch : str) {
      if (!isWhitespace(ch)) return false;
    }
    return true;
  }

  bool StrTools::isUppercaseLetter(CR_CH ch) {
    return ch >= 'A' && ch <= 'Z';
  }

  bool StrTools::isLowercaseLetter(CR_CH ch) {
    return ch >= 'a' && ch <= 'z';
  }

  bool StrTools::isLetter(CR_CH ch) {
    return isUppercaseLetter(ch) || isLowercaseLetter(ch);
  }

  /** Number Detectors */

  bool StrTools::isDigit(CR_CH ch) {
    return ch >= '0' && ch <= '9';
  }

  bool StrTools::isInteger(CR_STR str) {

    for (CR_CH ch : str) {
      if (!StrTools::isDigit(ch)) {
        return false;
      }
    }

    return true;
  }

  bool StrTools::isFloatingPoint(
    CR_STR str, CR_CH decPtSign
  ) {
    bool decPtFound = false;

    for (CR_CH ch : str) {
      if (!decPtFound && ch == decPtSign) {
        decPtFound = true;
      }
      else if (!StrTools::isDigit(ch)) {
        return false;
      }
    }

    return true;
  }

  VEC_STR StrTools::argvToStringVector(
    CR_INT argc, char *argv[]
  ) {
    // strings converted from 'argv'
    VEC_STR raws;

    /**
     * Load the vector 'raws'.
     * Skip the first 'argv' as it is the program name.
     */
    for (int i = 1; i < argc; i++) {
      raws.push_back(std::string(argv[i]));
    }

    return raws;
  }
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_CPP__