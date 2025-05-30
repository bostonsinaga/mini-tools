#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_TPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_TPP__

#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR wordKeywords,
    CR_VEC_STR numberKeywords,
    CR_VEC_STR toggleKeywords
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

    /** Initialize unordered maps with empty vector */

    for (CR_STR key : wordKeywords) {
      words[key] = {};
    }

    for (CR_STR key : numberKeywords) {
      numbers[key] = {};
    }

    for (CR_STR key : toggleKeywords) {
      toggles[key] = {};
    }

    /** Assign unordered maps with the 'raws' */

    std::string keyword;
    bool toggleHasInput = false;

    enum FoundEnum {
      entry_, word_, number_, toggle_
    } found_ = entry_;

    std::function<void(const FoundEnum&, CR_INT)> setKeyword = [&](
      const FoundEnum& newFound,
      CR_INT rawsIndex
    )->void {
      if (found_ == toggle_) {
        toggles[keyword].push_back(true);
      }

      keyword = raws[rawsIndex];
      found_ = newFound;
    };

    for (int i = 0; i < raws.size(); i++) {

      // keywords detected
      if (STRUNORMAP_FOUND<VEC_STR>(words, raws[i])) {
        setKeyword(word_, i);
      }
      else if (STRUNORMAP_FOUND<VEC<T>>(numbers, raws[i])) {
        setKeyword(number_, i);
      }
      else if (STRUNORMAP_FOUND<VEC_BOL>(toggles, raws[i])) {
        toggleHasInput = false;
        setKeyword(toggle_, i);
      }
      // inputs detected
      else if (found_ == word_) {
        words[keyword].push_back(raws[i]);
      }
      else if (found_ == number_) {
        numbers[keyword].push_back(
          StrTools::stringToNumber<T>(raws[i])
        );
      }
      else if (found_ == toggle_) {
        toggleHasInput = true;

        toggles[keyword].push_back(
          booleanize(raws[i])
        );
      }
      // before any keyword (basic string)
      else entries[raws[i]] = true;
    }

    // keyword toggle is specified without input at the last 'raws'
    if (!toggleHasInput && found_ == toggle_) {
      toggles[keyword].push_back(true);
    }
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::enter(CR_VEC_STR expectedEntries) {
    int found = 0;

    for (CR_STR expected : expectedEntries) {

      if (STRUNORMAP_BOL_FOUND(entries, expected)) {
        found++;
      }
    }

    return expectedEntries.size() == found;
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::booleanize(std::string &str) {

    int num = 0;
    StrTools::changeStringToUppercase(str);

    try { num = std::stoi(str); }
    catch (...) {}

    return (
      num != 0 || str == "TRUE" ||
      str == "YES" || str == "Y"
    );
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::wordsHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<VEC_STR>(words, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::numbersHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<VEC<T>>(numbers, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::togglesHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<VEC_BOL>(toggles, keyword);
  }

  template <inspector::NUMBER T>
  std::string CLIParser<T>::getWordAt(CR_STR keyword, CR_SZ index) {

    if (wordsHas(keyword) &&
      index < words[keyword].size()
    ) {
      return words[keyword][index];
    }

    return "";
  }

  template <inspector::NUMBER T>
  T CLIParser<T>::getNumberAt(CR_STR keyword, CR_SZ index) {

    if (numbersHas(keyword) &&
      index < numbers[keyword].size()
    ) {
      return numbers[keyword][index];
    }

    return T();
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::getToggleAt(CR_STR keyword, CR_SZ index) {

    if (togglesHas(keyword) &&
      index < toggles[keyword].size()
    ) {
      return toggles[keyword][index];
    }

    return false;
  }

  template <inspector::NUMBER T>
  VEC_STR CLIParser<T>::extractBasicStrings() {
    VEC_STR keywords;

    for (CR_PAIR2<std::string, bool> pair : entries) {
      keywords.push_back(pair.first);
    }

    return keywords;
  }

  template <inspector::NUMBER T>
  VEC_STR CLIParser<T>::getWords(
    CR_STR keyword,
    CR_BOL needClean
  ) {
    if (wordsHas(keyword)) {

      if (needClean) {
        return std::move(words[keyword]);
      }

      return words[keyword];
    }

    return {};
  }

  template <inspector::NUMBER T>
  VEC<T> CLIParser<T>::getNumbers(
    CR_STR keyword,
    CR_BOL needClean
  ) {
    if (numbersHas(keyword)) {

      if (needClean) {
        return std::move(numbers[keyword]);
      }

      return numbers[keyword];
    }

    return {};
  }

  template <inspector::NUMBER T>
  VEC_BOL CLIParser<T>::getToggles(
    CR_STR keyword,
    CR_BOL needClean
  ) {
    if (togglesHas(keyword)) {

      if (needClean) {
        return std::move(toggles[keyword]);
      }

      return toggles[keyword];
    }

    return {};
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_TPP__