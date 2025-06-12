#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_TPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_TPP__

#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  template <inspector::NUMBER T>
  template <typename U>
  void CLIParser<T>::pushDefault(
    UNORMAP_MAIN<U> unormap,
    CR_STR keyword,
    CR_FoundEnum found
  ) {
    if (found == limitFoundEnum<U>()) {
      unormap[keyword].first.push_back(unormap[keyword].second);
    }
  }

  template <inspector::NUMBER T>
  template <typename U, typename V>
  void CLIParser<T>::pushDefault(
    UNORMAP_MAIN<U> unormap_U,
    UNORMAP_MAIN<V> unormap_V,
    CR_STR keyword,
    CR_FoundEnum found
  ) {
    if (found == limitFoundEnum<U>()) {
      unormap_U[keyword].first.push_back(unormap_U[keyword].second);
    }
    else if (found == limitFoundEnum<V>()) {
      unormap_V[keyword].first.push_back(unormap_V[keyword].second);
    }
  }

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
  template <typename U>
  constexpr CLIParser<T>::FoundEnum CLIParser<T>::limitFoundEnum() const {
    if constexpr (std::is_same<U, std::string>::value) {
      return FoundWord;
    }
    else if constexpr (std::is_same<U, bool>::value) {
      return FoundToggle;
    }
    return FoundNumber;
  }

  template <inspector::NUMBER T>
  template <typename U>
  constexpr CLIParser<T>::FoundEnum CLIParser<T>::limitFoundEnumInput() const {

    if constexpr (std::is_same<U, std::string>::value) {
      return FoundWordInput;
    }
    else if constexpr (std::is_same<U, bool>::value) {
      return FoundToggleInput;
    }
    return FoundNumberInput;
  }

  /** CONSTRUCTORS */

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_WORD keywordDefaultWords,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
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
    CR_VEC_KEYDEF_WORD keywordDefaultWords,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
  ) {
    set<std::string, T>(
      words, numbers, raws,
      keywordDefaultWords,
      keywordDefaultNumbers
    );
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
  ) {
    set<T, bool>(
      numbers, toggles, raws,
      keywordDefaultNumbers,
      keywordDefaultToggles
    );
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_WORD keywordDefaultWords,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
  ) {
    set<std::string, bool>(
      words, toggles, raws,
      keywordDefaultWords,
      keywordDefaultToggles
    );
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_WORD keywordDefaultWords
  ) {
    set<std::string>(words, raws, keywordDefaultWords);
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
  ) {
    set<T>(numbers, raws, keywordDefaultNumbers);
  }

  template <inspector::NUMBER T>
  CLIParser<T>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
  ) {
    set<bool>(toggles, raws, keywordDefaultToggles);
  }

  /** SETTERS */

  template <inspector::NUMBER T>
  template <typename U>
  void CLIParser<T>::set(
    UNORMAP_MAIN<U> &unormap,
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<U> keywordDefaultVector
  ) {
    /** Initialization */

    for (CR_KEYDEF<U> pair : keywordDefaultVector) {
      unormap[pair.first] = {{}, pair.second};
    }

    std::string keyword;
    UI entriesOrderIndex = 0;
    FoundEnum found = FoundEntry;

    /** 'raws' iteration */

    for (int i = 0; i < raws.size(); i++) {

      // keyword detected
      if (has<U>(unormap, raws[i])) {
        pushDefault<U>(unormap, keyword, found);
        found = limitFoundEnum<U>();
        keyword = raws[i];
      }
      // input detected
      else if (found == limitFoundEnum<U>() && found == limitFoundEnumInput<U>()) {
        found = limitFoundEnumInput<U>();
        unormap[keyword].first.push_back(raws[i]);
      }
      // before any keyword of 'unormap' (basic string)
      else {
        entries[raws[i]] = entriesOrderIndex;
        entriesOrderIndex++;
      }
    }

    // a keyword is specified without input at the last 'raws'
    pushDefault<U>(unormap, keyword, found);
  }

  template <inspector::NUMBER T>
  template <typename U, typename V>
  void CLIParser<T>::set(
    UNORMAP_MAIN<U> &unormap_U,
    UNORMAP_MAIN<U> &unormap_V,
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<U> keywordDefaultVector_U,
    CR_VEC_KEYDEF<V> keywordDefaultVector_V
  ) {
    /** Initialization */

    for (CR_KEYDEF<U> pair : keywordDefaultVector_U) {
      unormap_U[pair.first] = {{}, pair.second};
    }

    for (CR_KEYDEF<V> pair : keywordDefaultVector_V) {
      unormap_V[pair.first] = {{}, pair.second};
    }

    std::string keyword;
    UI entriesOrderIndex = 0;
    FoundEnum found = FoundEntry;

    /** 'raws' iteration */

    for (int i = 0; i < raws.size(); i++) {

      // keywords detected
      if (has<U>(unormap_U, raws[i])) {
        pushDefault<U, V>(unormap_U, unormap_V, keyword, found);
        found = limitFoundEnum<U>();
        keyword = raws[i];
      }
      else if (has<V>(unormap_V, raws[i])) {
        pushDefault<U, V>(unormap_U, unormap_V, keyword, found);
        found = limitFoundEnum<V>();
        keyword = raws[i];
      }
      // inputs detected
      else if (found == limitFoundEnum<U>() && found == limitFoundEnumInput<U>()) {
        found = limitFoundEnumInput<U>();
        unormap_U[keyword].first.push_back(raws[i]);
      }
      else if (found == limitFoundEnum<V>() && found == limitFoundEnumInput<V>()) {
        found = limitFoundEnumInput<V>();
        unormap_V[keyword].first.push_back(raws[i]);
      }
      // before any keyword of 'unormap_' (basic string)
      else {
        entries[raws[i]] = entriesOrderIndex;
        entriesOrderIndex++;
      }
    }

    // a keyword is specified without input at the last 'raws'
    pushDefault<U, V>(unormap_U, unormap_V, keyword, found);
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_WORD keywordDefaultWords,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
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
    CR_VEC_KEYDEF_WORD keywordDefaultWords,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
  ) {
    set<std::string, T>(
      words, numbers, raws,
      keywordDefaultWords, keywordDefaultNumbers
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
  ) {
    set<T, bool>(
      numbers, toggles, raws,
      keywordDefaultNumbers, keywordDefaultToggles
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_WORD keywordDefaultWords,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
  ) {
    set<std::string, bool>(
      words, toggles, raws,
      keywordDefaultWords, keywordDefaultToggles
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_WORD keywordDefaultWords
  ) {
    set<std::string>(words, raws, keywordDefaultWords);
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_NUMBER keywordDefaultNumbers
  ) {
    set<T>(numbers, raws, keywordDefaultNumbers);
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF_TOGGLE keywordDefaultToggles
  ) {
    set<bool>(toggles, raws, keywordDefaultToggles);
  }

  /** CLEANERS */

  template <inspector::NUMBER T>
  void CLIParser<T>::cleanAll(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP_UI().swap(entries);
      STRUNORMAP<PAIR_WORD>().swap(words);
      STRUNORMAP<PAIR_NUMBER>().swap(numbers);
      STRUNORMAP<PAIR_TOGGLE>().swap(toggles);
    }
    else {
      entries.clear();
      words.clear();
      numbers.clear();
      toggles.clear();
    }
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::cleanEntries(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP_UI().swap(entries);
    }
    else entries.clear();
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::cleanWords(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP<PAIR_WORD>().swap(words);
    }
    else words.clear();
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::cleanNumbers(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP<PAIR_NUMBER>().swap(numbers);
    }
    else numbers.clear();
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::cleanToggles(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP<PAIR_TOGGLE>().swap(toggles);
    }
    else toggles.clear();
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
  template <typename U>
  bool CLIParser<T>::has(
    UNORMAP_MAIN<U> &unormap,
    CR_STR keyword
  ) {
    return STRUNORMAP_FOUND<PAIR_MAIN<U>>(unormap, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::wordsHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<PAIR_WORD>(words, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::numbersHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<PAIR_NUMBER>(numbers, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::togglesHas(CR_STR keyword) {
    return STRUNORMAP_FOUND<PAIR_TOGGLE>(toggles, keyword);
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::wordContains(CR_STR keyword) {
    return getSizeAtWords(keyword) > 0;
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::numberContains(CR_STR keyword) {
    return getSizeAtNumbers(keyword) > 0;
  }

  template <inspector::NUMBER T>
  bool CLIParser<T>::toggleContains(CR_STR keyword) {
    return getSizeAtToggles(keyword) > 0;
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
  VEC_STR CLIParser<T>::getVectorAtWords(
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
  VEC<T> CLIParser<T>::getVectorAtNumbers(
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
  VEC_BOL CLIParser<T>::getVectorAtToggles(
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
  size_t CLIParser<T>::getSizeAtWords(CR_STR keyword) {

    if (wordsHas(keyword)) {
      return words[keyword].first.size();
    }

    return 0;
  }

  template <inspector::NUMBER T>
  size_t CLIParser<T>::getSizeAtNumbers(CR_STR keyword) {

    if (numbersHas(keyword)) {
      return numbers[keyword].first.size();
    }

    return 0;
  }

  template <inspector::NUMBER T>
  size_t CLIParser<T>::getSizeAtToggles(CR_STR keyword) {

    if (togglesHas(keyword)) {
      return toggles[keyword].first.size();
    }

    return 0;
  }

  template <inspector::NUMBER T>
  template <typename U>
  size_t CLIParser<T>::getMax(
    UNORMAP_MAIN<U> &unormap,
    CR_VEC_KEYDEF<U> keywordPaddingVector
  ) {
    size_t max = 0;

    /**
     * Only use keywords from 'keywordPaddingVector' instead of using keyword
     * specific vector because 'balance' parameter contains 'keywordPaddingVector'
     * as well and this function is called inside it in balancers. 
     * This can avoid redundant keyword extraction process.
     */
    for (CR_KEYDEF<U> keypad : keywordPaddingVector) {
      if (has<U>(unormap, keypad.first)) {

        if (unormap[keypad.first].first.size() > max) {
          max = unormap[keypad.first].first.size();
        }
      }
    }

    return max;
  }

  /** BALANCERS */

  template <inspector::NUMBER T>
  template <typename U>
  void CLIParser<T>::balance(
    UNORMAP_MAIN<U> &unormap,
    CR_VEC_KEYDEF<U> keywordPaddingVector,
    CR_SZ max
  ) {
    VEC<U> additions;
    size_t difference = 0;

    /**
     * Equalize the vectors of 'unormap' with padding
     * values from 'keywordPaddingVector' ​​to balance them.
     */
    for (CR_KEYDEF<U> keypad : keywordPaddingVector) {
      if (has<U>(unormap, keypad.first)) {

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
  template <typename U, typename V>
  void CLIParser<T>::balance(
    UNORMAP_MAIN<U> &unormap_U,
    UNORMAP_MAIN<V> &unormap_V,
    CR_VEC_KEYDEF<U> keywordPaddingVector_U,
    CR_VEC_KEYDEF<V> keywordPaddingVector_V
  ) {
    size_t max[3] = {
      getMax<U>(unormap_U, keywordPaddingVector_U),
      getMax<V>(unormap_V, keywordPaddingVector_V),
      0
    };

    /** Find the highest value from the array as 'max[2]' */

    if (max[0] > max[1]) max[2] = max[0];
    else max[2] = max[1];

    /** Balance 2 unordered maps up to size 'max[2]' */

    balance<U>(unormap_U, keywordPaddingVector_U, max[2]);
    balance<V>(unormap_V, keywordPaddingVector_V, max[2]);
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_KEYDEF_WORD keywordPaddingWords
  ) {
    balance<std::string>(
      words,
      keywordPaddingWords,
      getMax<std::string>(words, keywordPaddingWords)
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers
  ) {
    balance<T>(
      numbers,
      keywordPaddingNumbers,
      getMax<T>(numbers, keywordPaddingNumbers)
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
  ) {
    balance<bool>(
      toggles,
      keywordPaddingToggles,
      getMax<bool>(toggles, keywordPaddingToggles)
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_KEYDEF_WORD keywordPaddingWords,
    CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers
  ) {
    balance<std::string, T>(
      words,
      numbers,
      keywordPaddingWords,
      keywordPaddingNumbers
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers,
    CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
  ) {
    balance<T, bool>(
      numbers,
      toggles,
      keywordPaddingNumbers,
      keywordPaddingToggles
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_KEYDEF_WORD keywordPaddingWords,
    CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
  ) {
    balance<std::string, bool>(
      words,
      toggles,
      keywordPaddingWords,
      keywordPaddingToggles
    );
  }

  template <inspector::NUMBER T>
  void CLIParser<T>::balance(
    CR_VEC_KEYDEF_WORD keywordPaddingWords,
    CR_VEC_KEYDEF_NUMBER keywordPaddingNumbers,
    CR_VEC_KEYDEF_TOGGLE keywordPaddingToggles
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
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_TPP__