#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_TPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_TPP__

#include "utils/vec_tools.hpp"

namespace mini_tools {
namespace utils {

  //_________|
  // NUMBERS |
  //_________|

  template <inspector::NUMBER T>
  CLI_NumberParser<T>::CLI_NumberParser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR keywords
  ) : CLI_TitleParser(argc, argv, keywords) {

    for (CR_STR key : keywords) {
      numbers[key] = {};
    }

    assign();
  }

  template <inspector::NUMBER T>
  void CLI_NumberParser<T>::assignTryCatch(CR_INT i, CR_INT j) {

    // try to all possible number types
    try {
      if constexpr (std::is_same_v<T, int>) {
        numbers[raws[i]].push_back(std::stoi(raws[j]));
      }
      else if constexpr (std::is_same_v<T, LI>) {
        numbers[raws[i]].push_back(std::stol(raws[j]));
      }
      else if constexpr (std::is_same_v<T, LLI>) {
        numbers[raws[i]].push_back(std::stoll(raws[j]));
      }
      else if constexpr (std::is_same_v<T, ULI>) {
        numbers[raws[i]].push_back(std::stoul(raws[j]));
      }
      else if constexpr (std::is_same_v<T, ULLI>) {
        numbers[raws[i]].push_back(std::stoull(raws[j]));
      }
      else if constexpr (std::is_same_v<T, float>) {
        numbers[raws[i]].push_back(std::stof(raws[j]));
      }
      else if constexpr (std::is_same_v<T, double>) {
        numbers[raws[i]].push_back(std::stod(raws[j]));
      }
      else if constexpr (std::is_same_v<T, LD>) {
        numbers[raws[i]].push_back(std::stold(raws[j]));
      }
      else numbers[raws[i]].push_back(0);
    }
    // the 'raws[j]' ​​start with non-numeric
    catch (...) {
      numbers[raws[i]].push_back(0);
    }
  }

  template <inspector::NUMBER T>
  void CLI_NumberParser<T>::assign() {
    for (int i = 0; i < raws.size(); i++) {

      // now is keyword
      if (has(raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {

          // next is keyword
          if (has(raws[j])) {
            i = j-1;
            break;
          }
          // input detected
          else CLI_NumberParser<T>::assignTryCatch(i, j);
        }
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

    if (STRUNORMAP_FOUND<VEC<T>>(numbers, keyword)) {
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
  CLI_WordParser(argc, argv, wordKeywords),
  CLI_NumberParser<T>(argc, argv, numberKeywords),
  CLI_ToggleParser(argc, argv, toggleKeywords)
  { assign(); }

  template <inspector::NUMBER T>
  void CLI_Parser<T>::assign() {
    for (int i = 0; i < raws.size(); i++) {

      // now is keyword WORDS
      if (CLI_WordParser::has(raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {

          // next is keyword
          if (has(raws[j])) {
            i = j-1;
            break;
          }
          // input detected
          else words[raws[i]].push_back(raws[j]);
        }
      }
      // now is keyword NUMBERS
      else if (CLI_NumberParser<T>::has(raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {

          // next is keyword
          if (has(raws[j])) {
            i = j-1;
            break;
          }
          // input detected
          else CLI_NumberParser<T>::assignTryCatch(i, j);
        }
      }
      // now is keyword TOGGLES
      else if (CLI_ToggleParser::has(raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {

          // next is keyword
          if (has(raws[j])) {
            i = j-1;
            break;
          }
          // input detected
          else toggles[raws[i]].push_back(
            booleanize(raws[j])
          );
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