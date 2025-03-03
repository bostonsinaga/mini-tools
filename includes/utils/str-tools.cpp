#ifndef __MINI_TOOLS__UTILS__STR_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__STR_TOOLS_CPP__

#include <algorithm>
#include "str-tools.h"

namespace mini_tools {
namespace utils {

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

  void StrTools::tidyUp(std::string &text) {

    // start with capital letter
    for (int i = 0; i < text.length(); i++) {
      if (!isWhitespace(text[i])) {
        changeCharToUppercase(text, i);
        break;
      }
    }

    // end with period
    for (int i = text.length(); i >= 0; i--) {
      if (!isWhitespace(text[i])) {
        text.insert(i, ".");
        break;
      }
    }

    /** Inner Tidying */

    enum {space, newline};
    bool willCapitalized = false;
    VEC_INT excessIndexes[2];

    for (int i = 0; i < text.length(); i++) {
      // dot detected
      if (text[i] == '.') {
        willCapitalized = true;
      }
      // change to uppercase
      else if (isLetter(text[i])) {
        if (willCapitalized) {
          changeToUppercase(text[i]);
          willCapitalized = false;
        }
      }
      // numbers ignored
      else if (isDigit(text[i])) {
        willCapitalized = false;
      }
      // replace tab to space
      else if (text[i] == '\t') {
        text[i] = ' ';
        excessIndexes[space].push_back(i);
      }
      // replace carriage return to newline
      else if (text[i] == '\r') {
        text[i] = '\n';
        excessIndexes[newline].push_back(i);
      }
      // space detected
      else if (text[i] == ' ') {
        excessIndexes[space].push_back(i);
      }
      // newline detected
      else if (text[i] == '\n') {
        excessIndexes[newline].push_back(i);
      }
    }

    /** Slice Excess Spaces */

    int pivot, duplicateCount, lastIndex;
    bool isNextEqual;
    VEC_PAIR<int> boundaries;

    for (int i = 0; i < 2; i++) {

      // reset
      lastIndex = int(excessIndexes[i].size()) - 1;
      pivot = 0;
      duplicateCount = 0;

      // detect index with a difference of one
      for (int j = 0; j < lastIndex; j++) {
        isNextEqual = excessIndexes[i][j] + 1 == excessIndexes[i][j+1];

        // yes
        if (isNextEqual) duplicateCount++;

        // no or the last 'j'
        if (!isNextEqual || j == lastIndex - 1) {

          // first duplication index marked
          if (duplicateCount > 0) {

            boundaries.push_back({
              excessIndexes[i][pivot],
              duplicateCount
            });

            duplicateCount = 0;
          }

          // checkpoint
          pivot = j+1;
        }
      }
    }

    // whitespaces boundary indexes united
    std::sort(boundaries.begin(), boundaries.end());

    // remove the duplicates
    for (int i = 0; i < boundaries.size(); i++) {

      text = text.substr(0, boundaries[i].first + 1)
        + text.substr(boundaries[i].first + boundaries[i].second + 1);

      // adjust to the rest
      for (int j = i+1; j < boundaries.size(); j++) {
        boundaries[j].first -= boundaries[i].second - 1;
      }
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__STR_TOOLS_CPP__