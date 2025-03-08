#ifndef __MINI_TOOLS__DATA_STRUCTURES__STR_TOOLS_CPP__
#define __MINI_TOOLS__DATA_STRUCTURES__STR_TOOLS_CPP__

#include <algorithm>
#include "data-structures/str-tools.h"

namespace mini_tools {
namespace data_structures {

  void StrTools::changeCase(char &ch, CR_BOL isUpper) {
    if (isUpper) {
      ch = std::toupper(ch);
    }
    else ch = std::tolower(ch);
  }

  void StrTools::changeToLowercase(char &ch) {
    changeCase(ch, false);
  }

  void StrTools::changeToUppercase(char &ch) {
    changeCase(ch, true);
  }

  char StrTools::getToLowercase(char ch) {
    changeCase(ch, false);
    return ch;
  }

  char StrTools::getToUppercase(char ch) {
    changeCase(ch, true);
    return ch;
  }

  void StrTools::changeCharCase(
    std::string &str,
    CR_LI index,
    CR_BOL isUpper
  ) {
    if (index >= 0 && index < str.length()) {
      changeCase(str[index], isUpper);
    }
  }

  void StrTools::changeCharToLowercase(
    std::string &str,
    CR_LI index
  ) {
    changeCharCase(str, index, false);
  }

  void StrTools::changeCharToUppercase(
    std::string &str,
    CR_LI index
  ) {
    changeCharCase(str, index, true);
  }

  std::string StrTools::getCharToLowercase(
    std::string str,
    CR_LI index
  ) {
    changeCharCase(str, index, false);
    return str;
  }

  std::string StrTools::getCharToUppercase(
    std::string str,
    CR_LI index
  ) {
    changeCharCase(str, index, true);
    return str;
  }

  void StrTools::changeStringCase(std::string &str, CR_BOL isUpper) {
    std::transform(
      str.begin(),
      str.end(),
      str.begin(),
      [&](unsigned char c) {
        if (isUpper) return std::toupper(c);
        else return std::tolower(c);
      }
    );
  }

  void StrTools::changeStringsCase(VEC_STR &vecStr, CR_BOL isUpper) {
    for (int i = 0; i < vecStr.size(); i++) {
      changeStringCase(vecStr.at(i), isUpper);
    }
  }

  void StrTools::changeStringToLowercase(std::string &str) {
    changeStringCase(str, false);
  }

  void StrTools::changeStringToUppercase(std::string &str) {
    changeStringCase(str, true);
  }

  std::string StrTools::getStringToLowercase(std::string str) {
    changeStringCase(str, false);
    return str;
  }

  std::string StrTools::getStringToUppercase(std::string str) {
    changeStringCase(str, true);
    return str;
  }

  void StrTools::changeStringsToLowercase(VEC_STR &vecStr) {
    changeStringsCase(vecStr, false);
  }

  void StrTools::changeStringsToUppercase(VEC_STR &vecStr) {
    changeStringsCase(vecStr, true);
  }

  std::string StrTools::uniteVector(
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
        changeCharToUppercase(text, i);
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
          changeToUppercase(text[i]);
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
}}

#endif // __MINI_TOOLS__DATA_STRUCTURES__STR_TOOLS_CPP__