#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_TPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_TPP__

#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  //_________|
  // NUMBERS |
  //_________|

  template <inspector::NUMBER T>
  CLI_NumberParser<T>::CLI_NumberParser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR keywords,
    CR_BOL assigning
  ) : CLI_TitleParser(argc, argv, keywords) {

    for (CR_STR key : keywords) {
      numbers[key] = {};
    }

    if (assigning) assign();
  }

  template <inspector::NUMBER T>
  void CLI_NumberParser<T>::assignTryCatch(CR_INT i, CR_INT j) {

    // try to all possible number types
    try {
      if constexpr (std::is_same_v<T, int>) {
        numbers[raws[j]].push_back(std::stoi(raws[i]));
      }
      else if constexpr (std::is_same_v<T, LI>) {
        numbers[raws[j]].push_back(std::stol(raws[i]));
      }
      else if constexpr (std::is_same_v<T, LLI>) {
        numbers[raws[j]].push_back(std::stoll(raws[i]));
      }
      else if constexpr (std::is_same_v<T, ULI>) {
        numbers[raws[j]].push_back(std::stoul(raws[i]));
      }
      else if constexpr (std::is_same_v<T, ULLI>) {
        numbers[raws[j]].push_back(std::stoull(raws[i]));
      }
      else if constexpr (std::is_same_v<T, float>) {
        numbers[raws[j]].push_back(std::stof(raws[i]));
      }
      else if constexpr (std::is_same_v<T, double>) {
        numbers[raws[j]].push_back(std::stod(raws[i]));
      }
      else if constexpr (std::is_same_v<T, LD>) {
        numbers[raws[j]].push_back(std::stold(raws[i]));
      }
      else numbers[raws[j]].push_back(0);
    }
    // the 'raws[i]' ​​start with non-numeric
    catch (...) {
      numbers[raws[j]].push_back(0);
    }
  }

  template <inspector::NUMBER T>
  void CLI_NumberParser<T>::assign() {
    int j = -1;

    for (int i = 0; i < raws.size(); i++) {
      // keyword detected
      if (has(raws[i])) {
        j = i;
      }
      // input detected
      else if (j >= 0) {
        CLI_NumberParser<T>::assignTryCatch(i, j);
      }
      // set titles in early iterations
      else titles[raws[i]] = true;
    }
  }

  template <inspector::NUMBER T>
  bool CLI_NumberParser<T>::has(CR_STR keyword) {
    return STRUNORMAP_FOUND<VEC<T>>(numbers, keyword);
  }

  template <inspector::NUMBER T>
  size_t CLI_NumberParser<T>::size(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC<T>>(numbers, keyword)) {
      return numbers[keyword].size();
    }

    return 0;
  }

  template <inspector::NUMBER T>
  T CLI_NumberParser<T>::at(CR_STR keyword, CR_SZ index) {

    if (STRUNORMAP_FOUND<VEC<T>>(numbers, keyword) &&
      index < numbers[keyword].size()
    ) {
      return numbers[keyword][index];
    }

    return T();
  }

  template <inspector::NUMBER T>
  T CLI_NumberParser<T>::last(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC<T>>(numbers, keyword) &&
      !numbers[keyword].empty()
    ) {
      return numbers[keyword].back();
    }

    return T();
  }

  template <inspector::NUMBER T>
  VEC<T> CLI_NumberParser<T>::extract(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC<T>>(numbers, keyword)) {
      return std::move(numbers[keyword]);
    }

    return {};
  }

  //________|
  // UNITED |
  //________|

  template <inspector::NUMBER T>
  CLI_Parser<T>::CLI_Parser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR wordKeywords,
    CR_VEC_STR numberKeywords,
    CR_VEC_STR toggleKeywords
  ):
  CLI_TitleParser(
    argc, argv,
    VecTools<std::string>::joinCopy(
      VecTools<std::string>::joinCopy(wordKeywords, numberKeywords),
      toggleKeywords
    )
  ),
  CLI_WordParser(argc, argv, wordKeywords, false),
  CLI_NumberParser<T>(argc, argv, numberKeywords, false),
  CLI_ToggleParser(argc, argv, toggleKeywords, false)
  { assign(); }

  template <inspector::NUMBER T>
  void CLI_Parser<T>::assign() {
    int j = -1;

    enum {
      word_e, number_e, toggle_e
    } index_e;

    for (int i = 0; i < raws.size(); i++) {
      // keyword detected WORDS
      if (CLI_WordParser::has(raws[i])) {
        index_e = word_e;
        j = i;
      }
      // keyword detected NUMBERS
      else if (CLI_NumberParser<T>::has(raws[i])) {
        index_e = number_e;
        j = i;
      }
      // keyword detected TOGGLES
      else if (CLI_ToggleParser::has(raws[i])) {
        index_e = toggle_e;
        j = i;
      }
      else if (j >= 0) {
        // input detected WORDS
        if (index_e == word_e) {
          words[raws[j]].push_back(raws[i]);
        }
        // input detected NUMBERS
        else if (index_e == number_e) {
          CLI_NumberParser<T>::assignTryCatch(i, j);
        }
        // input detected TOGGLES
        else if (index_e == toggle_e) {
          toggles[raws[j]].push_back(booleanize(raws[i]));
        }
      }
      // set titles in early iterations
      else titles[raws[i]] = true;
    }
  }

  template <inspector::NUMBER T>
  bool CLI_Parser<T>::has(CR_STR keyword) {
    return (
      STRUNORMAP_FOUND<VEC_STR>(words, keyword) ||
      STRUNORMAP_FOUND<VEC<T>>(CLI_NumberParser<T>::numbers, keyword) ||
      STRUNORMAP_FOUND<VEC_BOL>(toggles, keyword)
    );
  }

  template <inspector::NUMBER T>
  size_t CLI_Parser<T>::size(CR_STR keyword) {

    size_t sz = CLI_TitleParser::size();

    // select the class that the vector contains
    if (!sz) {
      sz = CLI_WordParser::size(keyword);

      if (!sz) {
        sz = CLI_NumberParser<T>::size(keyword);

        if (!sz) {
          return CLI_ToggleParser::size(keyword);
        }

        return sz;
      }

      return sz;
    }

    return sz;
  }

  template <inspector::NUMBER T>
  ARR_SZ<4> CLI_Parser<T>::sizes(CR_STR keyword) {
    return {
      CLI_TitleParser::size(),
      CLI_WordParser::size(keyword),
      CLI_NumberParser<T>::size(keyword),
      CLI_ToggleParser::size(keyword)
    };
  }

  template <inspector::NUMBER T>
  CLI_Parser<T>::CLI_VAL_TUPLE CLI_Parser<T>::at(CR_STR keyword, CR_SZ index) {
    return std::make_tuple(
      CLI_WordParser::at(keyword, index),
      CLI_NumberParser<T>::at(keyword, index),
      CLI_ToggleParser::at(keyword, index)
    );
  }

  template <inspector::NUMBER T>
  CLI_Parser<T>::CLI_VAL_TUPLE CLI_Parser<T>::last(CR_STR keyword) {
    return std::make_tuple(
      CLI_WordParser::last(keyword),
      CLI_NumberParser<T>::last(keyword),
      CLI_ToggleParser::last(keyword)
    );
  }

  template <inspector::NUMBER T>
  CLI_Parser<T>::CLI_VEC_TUPLE CLI_Parser<T>::extract(CR_STR keyword) {
    return std::make_tuple(
      CLI_WordParser::extract(keyword),
      CLI_NumberParser<T>::extract(keyword),
      CLI_ToggleParser::extract(keyword)
    );
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_TPP__