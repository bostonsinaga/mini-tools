#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_TPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_TPP__

#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  constexpr CLIParser<T, U, V>::UNORMAP_MAIN<W> CLIParser<T, U, V>::selectMainUnormap() {

    if constexpr (std::is_same_v<W, T>) {
      return mainUnormap_T;
    }
    else if constexpr (std::is_same_v<W, U>) {
      return mainUnormap_U;
    }
    else return mainUnormap_V;
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  bool CLIParser<T, U, V>::booleanize(std::string str) {

    int num = 0;
    utils::StrTools::changeStringToUppercase(str);

    try { num = std::stoi(str); }
    catch (...) {}

    return (
      num != 0 || str == "TRUE" ||
      str == "YES" || str == "Y"
    );
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <int N>
  void CLIParser<T, U, V>::pushDefault(
    CR_STR keyword,
    const FoundEnum &found
  ) {
    if constexpr (N == 1) {
      if (found == Found_T) {
        mainUnormap_T[keyword].first.push_back(
          mainUnormap_T[keyword].second
        );
      }
    }
    else if constexpr (N == 2) {
      if (found == Found_T) {
        mainUnormap_T[keyword].first.push_back(
          mainUnormap_T[keyword].second
        );
      }
      else if (found == Found_U) {
        mainUnormap_U[keyword].first.push_back(
          mainUnormap_U[keyword].second
        );
      }
    }
    else {
      if (found == Found_T) {
        mainUnormap_T[keyword].first.push_back(
          mainUnormap_T[keyword].second
        );
      }
      else if (found == Found_U) {
        mainUnormap_U[keyword].first.push_back(
          mainUnormap_U[keyword].second
        );
      }
      else if (found == Found_V) {
        mainUnormap_V[keyword].first.push_back(
          mainUnormap_V[keyword].second
        );
      }
    }
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  void CLIParser<T, U, V>::pushRaw(
    CR_STR keyword,
    CR_STR raw
  ) {
    if constexpr (std::is_same_v<W, bool>) {
      selectMainUnormap<W>()[keyword].first.push_back(booleanize(raw));
    }
    else if constexpr (inspector::isNumber<W>()) {
      selectMainUnormap<W>()[keyword].first.push_back(
        utils::StrTools::stringToNumber<W>(raw)
      );
    }
    else selectMainUnormap<W>()[keyword].first.push_back(raw);
  }

  /** CONSTRUCTORS */

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  CLIParser<T, U, V>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<T> keywordDefault_T
  ) {
    set(raws, keywordDefault_T);
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  CLIParser<T, U, V>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<T> keywordDefault_T,
    CR_VEC_KEYDEF<U> keywordDefault_U
  ) {
    set(
      raws,
      keywordDefault_T,
      keywordDefault_U
    );
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  CLIParser<T, U, V>::CLIParser(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<T> keywordDefault_T,
    CR_VEC_KEYDEF<U> keywordDefault_U,
    CR_VEC_KEYDEF<V> keywordDefault_V
  ) {
    set(
      raws,
      keywordDefault_T,
      keywordDefault_U,
      keywordDefault_V
    );
  }

  /** SETTERS */

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<T> keywordDefaultVector_T
  ) {
    /** Initialization */

    for (CR_KEYDEF<T> pair : keywordDefaultVector_T) {
      mainUnormap_T[pair.first] = {{}, pair.second};
    }

    std::string keyword;
    UI entriesOrderIndex = 0;
    FoundEnum found = FoundEntry;

    /** Iteration of 'raws' */

    for (int i = 0; i < raws.size(); i++) {

      // keyword detected
      if (has<T>(raws[i])) {
        pushDefault<1>(keyword, found);
        found = Found_T;
        keyword = raws[i];
      }
      // input detected
      else if (found == Found_T || found == FoundInput_T) {
        found = FoundInput_T;
        pushRaw<T>(keyword, raws[i]);
      }
      // before any keyword of 'mainUnormap_T' (basic string)
      else {
        entries[raws[i]] = entriesOrderIndex;
        entriesOrderIndex++;
      }
    }

    // a keyword is specified without input at the last 'raws'
    pushDefault<1>(keyword, found);
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<T> keywordDefaultVector_T,
    CR_VEC_KEYDEF<U> keywordDefaultVector_U
  ) {
    /** Initialization */

    for (CR_KEYDEF<T> pair : keywordDefaultVector_T) {
      mainUnormap_T[pair.first] = {{}, pair.second};
    }

    for (CR_KEYDEF<U> pair : keywordDefaultVector_U) {
      mainUnormap_U[pair.first] = {{}, pair.second};
    }

    std::string keyword;
    UI entriesOrderIndex = 0;
    FoundEnum found = FoundEntry;

    /** Iteration of 'raws' */

    for (int i = 0; i < raws.size(); i++) {

      // keywords detected
      if (has<T>(raws[i])) {
        pushDefault<2>(keyword, found);
        found = Found_T;
        keyword = raws[i];
      }
      else if (has<U>(raws[i])) {
        pushDefault<2>(keyword, found);
        found = Found_U;
        keyword = raws[i];
      }
      // inputs detected
      else if (found == Found_T || found == FoundInput_T) {
        found = FoundInput_T;
        pushRaw<T>(keyword, raws[i]);
      }
      else if (found == Found_U || found == FoundInput_U) {
        found = FoundInput_U;
        pushRaw<U>(keyword, raws[i]);
      }
      // before any keyword of main unordered maps (basic string)
      else {
        entries[raws[i]] = entriesOrderIndex;
        entriesOrderIndex++;
      }
    }

    // a keyword is specified without input at the last 'raws'
    pushDefault<2>(keyword, found);
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::set(
    CR_VEC_STR raws,
    CR_VEC_KEYDEF<T> keywordDefaultVector_T,
    CR_VEC_KEYDEF<U> keywordDefaultVector_U,
    CR_VEC_KEYDEF<V> keywordDefaultVector_V
  ) {
    /** Initialization */

    for (CR_KEYDEF<T> pair : keywordDefaultVector_T) {
      mainUnormap_T[pair.first] = {{}, pair.second};
    }

    for (CR_KEYDEF<U> pair : keywordDefaultVector_U) {
      mainUnormap_U[pair.first] = {{}, pair.second};
    }

    for (CR_KEYDEF<V> pair : keywordDefaultVector_V) {
      mainUnormap_V[pair.first] = {{}, pair.second};
    }

    std::string keyword;
    UI entriesOrderIndex = 0;
    FoundEnum found = FoundEntry;

    /** Iteration of 'raws' */

    for (int i = 0; i < raws.size(); i++) {

      // keywords detected
      if (has<T>(raws[i])) {
        pushDefault<3>(keyword, found);
        found = Found_T;
        keyword = raws[i];
      }
      else if (has<U>(raws[i])) {
        pushDefault<3>(keyword, found);
        found = Found_U;
        keyword = raws[i];
      }
      else if (has<V>(raws[i])) {
        pushDefault<3>(keyword, found);
        found = Found_V;
        keyword = raws[i];
      }
      // inputs detected
      else if (found == Found_T || found == FoundInput_T) {
        found = FoundInput_T;
        pushRaw<T>(keyword, raws[i]);
      }
      else if (found == Found_U || found == FoundInput_U) {
        found = FoundInput_U;
        pushRaw<U>(keyword, raws[i]);
      }
      else if (found == Found_V || found == FoundInput_V) {
        found = FoundInput_V;
        pushRaw<V>(keyword, raws[i]);
      }
      // before any keyword of main unordered maps (basic string)
      else {
        entries[raws[i]] = entriesOrderIndex;
        entriesOrderIndex++;
      }
    }

    // a keyword is specified without input at the last 'raws'
    pushDefault<3>(keyword, found);
  }

  /** CLEANERS */

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::cleanEntries(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP_UI().swap(entries);
    }
    else entries.clear();
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::cleanAll(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP_UI().swap(entries);
      STRUNORMAP<PAIR_MAIN<T>>().swap(mainUnormap_T);
      STRUNORMAP<PAIR_MAIN<U>>().swap(mainUnormap_U);
      STRUNORMAP<PAIR_MAIN<V>>().swap(mainUnormap_V);
    }
    else {
      entries.clear();
      mainUnormap_T.clear();
      mainUnormap_U.clear();
      mainUnormap_V.clear();
    }
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  void CLIParser<T, U, V>::clean(CR_BOL fullyClean) {
    if (fullyClean) {
      STRUNORMAP<W>().swap(selectMainUnormap<W>());
    }
    else selectMainUnormap<W>().clear();
  }

  /** INQUIRIES */

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  bool CLIParser<T, U, V>::enter(
    CR_VEC_STR expectedEntries,
    CR_BOL fromAllEntries
  ) {
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

    return fromAllEntries ?
      entries.size() == found :
      expectedEntries.size() == found;
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  bool CLIParser<T, U, V>::query(
    CR_VEC_STR expectedEntries,
    CR_BOL fromAllEntries
  ) {
    UI found = 0;

    for (CR_STR expected : expectedEntries) {

      if (STRUNORMAP_UI_FOUND(entries, expected)) {
        found++;
      }
    }

    return fromAllEntries ?
      entries.size() == found :
      expectedEntries.size() == found;
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  bool CLIParser<T, U, V>::has(CR_STR keyword) {
    return STRUNORMAP_FOUND<PAIR_MAIN<W>>(selectMainUnormap<W>(), keyword);
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  bool CLIParser<T, U, V>::contains(CR_STR keyword) {
    return getSizeAt<W>(keyword) > 0;
  }

  /** GETTERS */

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  W CLIParser<T, U, V>::getAt(CR_STR keyword, CR_SZ index) {

    if (has<W>(keyword) &&
      index < selectMainUnormap<W>()[keyword].first.size()
    ) {
      return selectMainUnormap<W>()[keyword].first[index];
    }

    return W();
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  VEC_STR CLIParser<T, U, V>::extractBasicStrings() {
    VEC_STR keywords;

    for (CR_PAIR2<std::string, UI> pair : entries) {
      keywords.push_back(pair.first);
    }

    return keywords;
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  VEC<W> CLIParser<T, U, V>::getVectorAt(
    CR_STR keyword,
    CR_BOL onlyCopy
  ) {
    if (has<W>(keyword)) {

      if (onlyCopy) return selectMainUnormap<W>()[keyword].first;
      return std::move(selectMainUnormap<W>()[keyword].first);
    }

    return {};
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  VEC_STR CLIParser<T, U, V>::argvToStringVector(
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

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  size_t CLIParser<T, U, V>::getSizeAt(CR_STR keyword) {

    if (has<W>(keyword)) {
      return selectMainUnormap<W>()[keyword].first.size();
    }

    return 0;
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  template <typename W>
  size_t CLIParser<T, U, V>::getMax(
    CR_VEC_KEYDEF<W> keywordPaddingVector
  ) {
    size_t max = 0;

    /**
     * Only use keywords from 'keywordPaddingVector' instead of using keyword
     * specific vector because 'balance' parameter contains 'keywordPaddingVector'
     * as well and this function is called inside it in balancers. 
     * This can avoid redundant keyword extraction process.
     */
    for (CR_KEYDEF<W> keypad : keywordPaddingVector) {
      if (has<W>(keypad.first)) {

        if (selectMainUnormap<W>()[keypad.first].first.size() > max) {
          max = selectMainUnormap<W>()[keypad.first].first.size();
        }
      }
    }

    return max;
  }

  /** BALANCERS */

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::balance(
    CR_VEC_KEYDEF<T> keywordPaddingVector_T,
    CR_SZ max
  ) {
    VEC<U> additions;
    size_t difference = 0;

    /**
     * Equalize the vectors of 'mainUnormap_T' with padding
     * values from 'keywordPaddingVector_T' ​​to balance them.
     */
    for (CR_KEYDEF<T> keypad : keywordPaddingVector_T) {
      if (has<T>(keypad.first)) {

        difference = max - mainUnormap_T[keypad.first].first.size();
        additions = VEC<T>(difference, keypad.second);

        mainUnormap_T[keypad.first].first.reserve(
          mainUnormap_T[keypad.first].first.size() + difference
        );

        mainUnormap_T[keypad.first].first.insert(
          mainUnormap_T[keypad.first].first.end(),
          additions.begin(),
          additions.end()
        );
      }
    }
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::balance(
    CR_VEC_KEYDEF<T> keywordPaddingVector_T
  ) {
    size_t max[2] = {
      getMax<T>(keywordPaddingVector_T), 0
    };

    if (max[0] > max[1]) max[1] = max[0];
    balance<T>(keywordPaddingVector_T, max[1]);
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::balance(
    CR_VEC_KEYDEF<T> keywordPaddingVector_T,
    CR_VEC_KEYDEF<U> keywordPaddingVector_U
  ) {
    size_t max[3] = {
      getMax<T>(keywordPaddingVector_T),
      getMax<U>(keywordPaddingVector_U),
      0
    };

    if (max[0] > max[1]) max[2] = max[0];
    else max[2] = max[1];

    balance<T>(keywordPaddingVector_T, max[2]);
    balance<U>(keywordPaddingVector_U, max[2]);
  }

  template <typename T, typename U, typename V>
  requires CLIUniqueType<T, U, V>
  void CLIParser<T, U, V>::balance(
    CR_VEC_KEYDEF<T> keywordPaddingVector_T,
    CR_VEC_KEYDEF<U> keywordPaddingVector_U,
    CR_VEC_KEYDEF<V> keywordPaddingVector_V
  ) {
    size_t max[4] = {
      getMax<T>(keywordPaddingVector_T),
      getMax<U>(keywordPaddingVector_U),
      getMax<V>(keywordPaddingVector_V),
      0
    };

    /** Find the highest value from the array as 'max[3]' */

    if (max[0] > max[1]) max[3] = max[0];
    else max[3] = max[1];

    if (max[2] > max[3]) max[3] = max[2];

    /** Balance 3 unordered maps up to size 'max[3]' */

    balance<T>(keywordPaddingVector_T, max[3]);
    balance<U>(keywordPaddingVector_U, max[3]);
    balance<V>(keywordPaddingVector_V, max[3]);
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_TPP__