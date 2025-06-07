#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_TPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_TPP__

#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  template <inspector::NUMBER T>
  void CLIParser<T>::pushDefault(
    CR_STR keyword,
    CR_FoundEnum found
  ) {
    if (found == FoundWord) {
      words[keyword].first.push_back(words[keyword].second);
    }
    else if (found == FoundNumber) {
      numbers[keyword].first.push_back(numbers[keyword].second);
    }
    else if (found == FoundToggle) {
      toggles[keyword].first.push_back(toggles[keyword].second);
    }
  }

  template <inspector::NUMBER T>
  CLIParser<T>::KeywordIgnoredVectorsTuple CLIParser<T>::convertKeywordIgnoredVectorsTuple(
    CR_VEC_STR wordKeywords,
    CR_VEC_STR numberKeywords,
    CR_VEC_STR toggleKeywords
  ) {
    VEC_PAIR<std::string> keywordDefaultWords;
    VEC_PAIR2<std::string, T> keywordDefaultNumbers;
    VEC_PAIR2<std::string, bool> keywordDefaultToggles;

    for (CR_STR key : wordKeywords) {
      keywordDefaultWords.push_back({key, ""});
    }

    for (CR_STR key : numberKeywords) {
      keywordDefaultNumbers.push_back({key, T()});
    }

    for (CR_STR key : toggleKeywords) {
      keywordDefaultToggles.push_back({key, false});
    }

    return std::make_tuple(
      keywordDefaultWords,
      keywordDefaultNumbers,
      keywordDefaultToggles
    );
  }

  template <inspector::NUMBER T>
  template <typename U>
  VEC_PAIR2<std::string, U> CLIParser<T>::convertKeywordPredefinedVector(
    MAIN_STRUNORMAP<U> &unormap,
    CR_VEC_STR keywords
  ) {
    VEC_PAIR2<std::string, U> keywordPaddingVector;

    // get the predefined default values
    for (CR_STR key : keywords) {
      if (STRUNORMAP_FOUND<PAIR_MAIN<U>>(unormap, key)) {
        keywordPaddingVector.push_back(
          {key, unormap[key].second}
        );
      }
    }

    return keywordPaddingVector;
  }

  /** EXPLICIT CONSTRUCTORS */

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_PAIR<std::string> keywordDefaultWords,
    CR_VEC_PAIR2<std::string, T> keywordDefaultNumbers,
    CR_VEC_PAIR2<std::string, bool> keywordDefaultToggles
  ) {
    set(
      raws,
      keywordDefaultWords,
      keywordDefaultNumbers,
      keywordDefaultToggles
    );
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_PAIR<std::string> keywordDefaultVector
  ) {
    set(raws, keywordDefaultVector, {}, {});
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_PAIR2<std::string, T> keywordDefaultVector
  ) {
    set(raws, {}, keywordDefaultVector, {});
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_PAIR2<std::string, bool> keywordDefaultVector
  ) {
    set(raws, {}, {}, keywordDefaultVector);
  }

  /** IGNORED CONSTRUCTORS */

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_STR wordKeywords,
    CR_VEC_STR numberKeywords,
    CR_VEC_STR toggleKeywords
  ) {
    set(
      raws,
      wordKeywords,
      numberKeywords,
      toggleKeywords
    );
  }

  template <inspector::NUMBER T>
  CLIParser<T> CLIParser<T>::createWords(
    CR_VEC_STR raws,
    CR_VEC_STR keywords
  ) {
    return CLIParser<T>(raws, keywords, {}, {});
  }

  template <inspector::NUMBER T>
  CLIParser<T> CLIParser<T>::createNumbers(
    CR_VEC_STR raws,
    CR_VEC_STR keywords
  ) {
    return CLIParser<T>(raws, {}, keywords, {});
  }

  template <inspector::NUMBER T>
  CLIParser<T> CLIParser<T>::createToggles(
    CR_VEC_STR raws,
    CR_VEC_STR keywords
  ) {
    return CLIParser<T>(raws, {}, {}, keywords);
  }

  /** EXPLICIT SETTERS */

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_PAIR<std::string> keywordDefaultWords,
    CR_VEC_PAIR2<std::string, T> keywordDefaultNumbers,
    CR_VEC_PAIR2<std::string, bool> keywordDefaultToggles
  ) {
    /** Initialize main unordered maps with empty vectors and default values */

    for (CR_PAIR_STR pair : keywordDefaultWords) {
      words[pair.first] = {{}, pair.second};
    }

    for (CR_PAIR2<std::string, T> pair : keywordDefaultNumbers) {
      numbers[pair.first] = {{}, pair.second};
    }

    for (CR_PAIR2<std::string, bool> pair : keywordDefaultToggles) {
      toggles[pair.first] = {{}, pair.second};
    }

    /** Set main unordered maps with the 'raws' */

    std::string keyword;
    UI entriesOrderIndex = 0;
    FoundEnum found = FoundEntry;

    for (int i = 0; i < raws.size(); i++) {

      // keywords detected
      if (wordsHas(raws[i])) {
        pushDefault(keyword, found);
        found = FoundWord;
        keyword = raws[i];
      }
      else if (numbersHas(raws[i])) {
        pushDefault(keyword, found);
        found = FoundNumber;
        keyword = raws[i];
      }
      else if (togglesHas(raws[i])) {
        pushDefault(keyword, found);
        found = FoundToggle;
        keyword = raws[i];
      }
      // inputs detected
      else if (found == FoundWord) {
        words[keyword].first.push_back(raws[i]);
      }
      else if (found == FoundNumber) {
        numbers[keyword].first.push_back(
          StrTools::stringToNumber<T>(raws[i])
        );
      }
      else if (found == FoundToggle) {
        toggles[keyword].first.push_back(
          booleanize(raws[i])
        );
      }
      // before any keyword of main unordered maps (basic string)
      else {
        entries[raws[i]] = entriesOrderIndex;
        entriesOrderIndex++;
      }
    }

    // a keyword is specified without input at the last 'raws'
    pushDefault(keyword, found);
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_PAIR<std::string> newKeywordDefaultVector
  ) {
    set(raws, newKeywordDefaultVector, {}, {});
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_PAIR2<std::string, T> newKeywordDefaultVector
  ) {
    set(raws, {}, newKeywordDefaultVector, {});
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_PAIR2<std::string, bool> newKeywordDefaultVector
  ) {
    set(raws, {}, {}, newKeywordDefaultVector);
  }

  /** IGNORED SETTERS */

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_STR wordKeywords,
    CR_VEC_STR numberKeywords,
    CR_VEC_STR toggleKeywords
  ) {
    KeywordIgnoredVectorsTuple tuple = convertKeywordIgnoredVectorsTuple(
      wordKeywords, numberKeywords, toggleKeywords
    );

    set(
      raws,
      std::get<0>(tuple),
      std::get<1>(tuple),
      std::get<2>(tuple)
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::setWords(
    CR_VEC_STR raws,
    CR_VEC_STR newKeywords
  ) {
    set(raws, newKeywords, {}, {});
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::setNumbers(
    CR_VEC_STR raws,
    CR_VEC_STR newKeywords
  ) {
    set(raws, {}, newKeywords, {});
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::setToggles(
    CR_VEC_STR raws,
    CR_VEC_STR newKeywords
  ) {
    set(raws, {}, {}, newKeywords);
  }

  /** INQUIRIES */

  template <inspector::NUMBER T>
  bool CLIParser<T>::enter(CR_VEC_STR expectedEntries) {
    UI found = 0, previousOrder = 0;

    for (CR_STR expected : expectedEntries) {

      if (STRUNORMAP_UI_FOUND(entries, expected) &&
        entries[expected] >= previousOrder
      ) {
        found++;
        previousOrder = entries[expected];
      }
      else return false;
    }

    return expectedEntries.size() == found;
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::query(CR_VEC_STR expectedEntries) {
    UI found = 0;

    for (CR_STR expected : expectedEntries) {

      if (STRUNORMAP_UI_FOUND(entries, expected)) {
        found++;
      }
    }

    return expectedEntries.size() == found;
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::booleanize(std::string str) {

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
    return STRUNORMAP_FOUND<PAIR_WORDS>(words, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::numbersHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<PAIR_NUMBERS>(numbers, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::togglesHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<PAIR_TOGGLES>(toggles, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::wordContains(CR_STR keyword) {
    return getWordSize(keyword) > 0;
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::numberContains(CR_STR keyword) {
    return getNumberSize(keyword) > 0;
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::toggleContains(CR_STR keyword) {
    return getToggleSize(keyword) > 0;
  }

  /** GETTERS */

  template <inspector::NUMBER T>
  std::string CLIParser<T>::getWordAt(CR_STR keyword, CR_SZ index) {

    if (wordsHas(keyword) &&
      index < words[keyword].first.size()
    ) {
      return words[keyword].first[index];
    }

    return "";
  }

  template <inspector::NUMBER T>
  T CLIParser<T>::getNumberAt(CR_STR keyword, CR_SZ index) {

    if (numbersHas(keyword) &&
      index < numbers[keyword].first.size()
    ) {
      return numbers[keyword].first[index];
    }

    return T();
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::getToggleAt(CR_STR keyword, CR_SZ index) {

    if (togglesHas(keyword) &&
      index < toggles[keyword].first.size()
    ) {
      return toggles[keyword].first[index];
    }

    return false;
  }

  template <inspector::NUMBER T>
  VEC_STR CLIParser<T>::extractBasicStrings() {
    VEC_STR keywords;

    for (CR_PAIR2<std::string, UI> pair : entries) {
      keywords.push_back(pair.first);
    }

    return keywords;
  }

  template <inspector::NUMBER T>
  VEC_STR CLIParser<T>::getWords(
    CR_STR keyword,
    CR_BOL onlyCopy
  ) {
    if (wordsHas(keyword)) {

      if (onlyCopy) return words[keyword].first;
      return std::move(words[keyword].first);
    }

    return {};
  }

  template <inspector::NUMBER T>
  VEC<T> CLIParser<T>::getNumbers(
    CR_STR keyword,
    CR_BOL onlyCopy
  ) {
    if (numbersHas(keyword)) {

      if (onlyCopy) return numbers[keyword].first;
      return std::move(numbers[keyword].first);
    }

    return {};
  }

  template <inspector::NUMBER T>
  VEC_BOL CLIParser<T>::getToggles(
    CR_STR keyword,
    CR_BOL onlyCopy
  ) {
    if (togglesHas(keyword)) {

      if (onlyCopy) return toggles[keyword].first;
      return std::move(toggles[keyword].first);
    }

    return {};
  }

  template <inspector::NUMBER T>
  VEC_STR CLIParser<T>::argvToStringVector(
    CR_INT argc,
    char *argv[]
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

  /** SIZE GETTERS */

  template <inspector::NUMBER T>
  size_t CLIParser<T>::getWordSize(CR_STR keyword) {

    if (wordsHas(keyword)) {
      return words[keyword].first.size();
    }

    return 0;
  }

  template <inspector::NUMBER T>
  size_t CLIParser<T>::getNumberSize(CR_STR keyword) {

    if (numbersHas(keyword)) {
      return numbers[keyword].first.size();
    }

    return 0;
  }

  template <inspector::NUMBER T>
  size_t CLIParser<T>::getToggleSize(CR_STR keyword) {

    if (togglesHas(keyword)) {
      return toggles[keyword].first.size();
    }

    return 0;
  }

  template <inspector::NUMBER T>
  template <typename U>
  size_t CLIParser<T>::getMax(
    MAIN_STRUNORMAP<U> &unormap,
    CR_VEC_PAIR2<std::string, U> keywordPaddingVector
  ) {
    size_t max = 0;

    /**
     * Only use keywords from 'keywordPaddingVector' instead of using keyword
     * specific vector because 'balance' parameter contains 'keywordPaddingVector'
     * as well and this function is called inside it in balancers. 
     * This can avoid redundant keyword extraction process.
     */
    for (CR_PAIR2<std::string, U> keypad : keywordPaddingVector) {
      if (STRUNORMAP_FOUND<PAIR_MAIN<U>>(unormap, keypad.first)) {

        if (unormap[keypad.first].first.size() > max) {
          max = unormap[keypad.first].first.size();
        }
      }
    }

    return max;
  }

  /** MULTIPLE EXPLICIT BALANCERS */

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_PAIR<std::string> keywordPaddingWords,
    CR_VEC_PAIR2<std::string, T> keywordPaddingNumbers,
    CR_VEC_PAIR2<std::string, bool> keywordPaddingToggles
  ) {
    size_t max[4] = {
      getMax<std::string>(words, keywordPaddingWords),
      getMax<T>(numbers, keywordPaddingNumbers),
      getMax<bool>(toggles, keywordPaddingToggles),
      0
    };

    /** Find the highest value from the array as 'max[3]' */

    if (max[0] > max[1]) max[3] = max[0];
    else max[3] = max[1];

    if (max[2] > max[3]) max[3] = max[2];

    /** Balance 3 unordered maps up to size 'max[3]' */

    balance<std::string>(words, keywordPaddingWords, max[3]);
    balance<T>(numbers, keywordPaddingNumbers, max[3]);
    balance<bool>(toggles, keywordPaddingToggles, max[3]);
  }

  /** MULTIPLE IGNORED BALANCERS */

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_STR wordKeywords,
    CR_VEC_STR numberKeywords,
    CR_VEC_STR toggleKeywords
  ) {
    VEC_PAIR<std::string> keywordPaddingWords
      = convertKeywordPredefinedVector<std::string>(words, wordKeywords);

    VEC_PAIR2<std::string, T> keywordPaddingNumbers
      = convertKeywordPredefinedVector<T>(numbers, numberKeywords);

    VEC_PAIR2<std::string, bool> keywordPaddingToggles
      = convertKeywordPredefinedVector<bool>(toggles, toggleKeywords);

    balance(
      keywordPaddingWords,
      keywordPaddingNumbers,
      keywordPaddingToggles
    );
  }

  /** SINGLE EXPLICIT BALANCERS */

  template <inspector::NUMBER T>
  template <typename U>
  void CLIParser<T>::balance(
    MAIN_STRUNORMAP<U> &unormap,
    CR_VEC_PAIR2<std::string, U> keywordPaddingVector,
    CR_SZ max
  ) {
    VEC<U> additions;
    size_t difference = 0;

    /**
     * Equalize the vectors of 'unormap' with padding
     * values from 'keywordPaddingVector' ​​to balance them.
     */
    for (CR_PAIR2<std::string, U> keypad : keywordPaddingVector) {
      if (STRUNORMAP_FOUND<PAIR_MAIN<U>>(unormap, keypad.first)) {

        difference = max - unormap[keypad.first].first.size();
        additions = VEC<U>(difference, keypad.second);

        unormap[keypad.first].first.reserve(
          unormap[keypad.first].first.size() + difference
        );

        unormap[keypad.first].first.insert(
          unormap[keypad.first].first.end(),
          additions.begin(),
          additions.end()
        );
      }
    }
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balanceWords(
    CR_VEC_PAIR<std::string> keywordPaddingVector
  ) {
    balance<std::string>(
      words,
      keywordPaddingVector,
      getMax<std::string>(words, keywordPaddingVector)
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balanceNumbers(
    CR_VEC_PAIR<T> keywordPaddingVector
  ) {
    balance<T>(
      numbers,
      keywordPaddingVector,
      getMax<T>(numbers, keywordPaddingVector)
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balanceToggles(
    CR_VEC_PAIR<bool> keywordPaddingVector
  ) {
    balance<bool>(
      toggles,
      keywordPaddingVector,
      getMax<bool>(toggles, keywordPaddingVector)
    );
  }

  /** SINGLE IGNORED BALANCERS */

  template <inspector::NUMBER T>
  template <typename U>
  void CLIParser<T>::balance(
    MAIN_STRUNORMAP<U> &unormap,
    CR_VEC_STR keywords
  ) {
    VEC_PAIR2<std::string, U> keywordPaddingVector
      = convertKeywordPredefinedVector<U>(unormap, keywords);

    balance<U>(
      unormap,
      keywordPaddingVector,
      getMax<U>(unormap, keywordPaddingVector)
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balanceWords(CR_VEC_STR keywords) {
    balance<std::string>(words, keywords);
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balanceNumbers(CR_VEC_STR keywords) {
    balance<T>(numbers, keywords);
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balanceToggles(CR_VEC_STR keywords) {
    balance<bool>(toggles, keywords);
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_TPP__