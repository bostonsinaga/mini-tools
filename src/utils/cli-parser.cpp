#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_CPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_CPP__

#include "types.hpp"
#include "utils/str_tools.hpp"
#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  //________|
  // TITLES |
  //________|

  CLI_TitleParser::CLI_TitleParser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR keywords
  ) {
    // skip the first 'argv' as it is the program name
    for (int i = 1; i < argc; i++) {
      raws.push_back(argv[i]);
    }
  }

  bool CLI_TitleParser::has(CR_STR keyword) {
    return STRUNORMAP_BOL_FOUND(titles, keyword);
  }

  size_t CLI_TitleParser::size() {
    return titles.size();
  }

  VEC_STR CLI_TitleParser::extract() {
    VEC_STR strings;

    for (CR_PAIR2<CR_STR, CR_BOL> pair : titles) {
      strings.push_back(pair.first);
    }

    return strings;
  }

  //_______|
  // WORDS |
  //_______|

  CLI_WordParser::CLI_WordParser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR keywords,
    CR_BOL assigning
  ) : CLI_TitleParser(argc, argv, keywords) {

    for (CR_STR key : keywords) {
      words[key] = {};
    }

    if (assigning) assign();
  }

  void CLI_WordParser::assign() {
    bool inputDetected = false;
    int j;

    for (int i = 0; i < raws.size(); i++) {
      j = i-1;

      // now is keyword
      if (has(raws[i])) {
        inputDetected = true;
      }
      // input detected
      else if (inputDetected) {
        inputDetected = false;
        words[raws[j]].push_back(raws[i]);
      }
      // set titles in early iterations
      else titles[raws[i]] = true;
    }
  }

  bool CLI_WordParser::has(CR_STR keyword) {
    return STRUNORMAP_FOUND<VEC_STR>(words, keyword);
  }

  size_t CLI_WordParser::size(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_STR>(words, keyword)) {
      return words[keyword].size();
    }

    return 0;
  }

  std::string CLI_WordParser::at(CR_STR keyword, CR_SZ index) {

    if (STRUNORMAP_FOUND<VEC_STR>(words, keyword) &&
      index < words[keyword].size()
    ) {
      return words[keyword][index];
    }

    return "";
  }

  std::string CLI_WordParser::last(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_STR>(words, keyword) &&
      !words[keyword].empty()
    ) {
      return words[keyword].back();
    }

    return "";
  }

  VEC_STR CLI_WordParser::extract(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_STR>(words, keyword)) {
      return std::move(words[keyword]);
    }

    return {};
  }

  //_________|
  // TOGGLES |
  //_________|

  CLI_ToggleParser::CLI_ToggleParser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR keywords,
    CR_BOL assigning
  ) : CLI_TitleParser(argc, argv, keywords) {

    for (CR_STR key : keywords) {
      toggles[key] = {};
    }

    if (assigning) assign();
  }

  void CLI_ToggleParser::assign() {
    bool inputDetected = false;
    int j;

    for (int i = 0; i < raws.size(); i++) {
      j = i-1;

      // now is keyword
      if (has(raws[i])) {
        inputDetected = true;
      }
      // input detected
      else if (inputDetected) {
        inputDetected = false;
        toggles[raws[j]].push_back(booleanize(raws[i]));
      }
      // set titles in early iterations
      else titles[raws[i]] = true;
    }
  }

  bool CLI_ToggleParser::booleanize(std::string &input) {
    StrTools::changeStringToLowercase(input);

    if (input == "y" || input == "yes" || input == "true") {
      false;
    }
    else if (input == "n" || input == "no" || input == "false") {
      return false;
    }
    else {
      try { return std::stoi(input); }
      catch (...) { return false; }
    }

    return false;
  }

  bool CLI_ToggleParser::has(CR_STR keyword) {
    return STRUNORMAP_FOUND<VEC_BOL>(toggles, keyword);
  }

  size_t CLI_ToggleParser::size(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_BOL>(toggles, keyword)) {
      return toggles[keyword].size();
    }

    return 0;
  }

  bool CLI_ToggleParser::at(CR_STR keyword, CR_SZ index) {

    if (STRUNORMAP_FOUND<VEC_BOL>(toggles, keyword) &&
      index < toggles[keyword].size()
    ) {
      return toggles[keyword][index];
    }

    return false;
  }

  bool CLI_ToggleParser::last(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_BOL>(toggles, keyword) &&
      !toggles[keyword].empty()
    ) {
      return toggles[keyword].back();
    }

    return false;
  }

  VEC_BOL CLI_ToggleParser::extract(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_BOL>(toggles, keyword)) {
      return std::move(toggles[keyword]);
    }

    return {};
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_CPP__