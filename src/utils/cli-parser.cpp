#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_CPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_CPP__

#include "types.hpp"
#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  void CLIParser::assignLast(
    CR_INT argc,
    char *argv[],
    STRUNORMAP_BOL &titles,
    STRUNORMAP_DBL &numbers,
    STRUNORMAP_STR &words
  ) {
    std::string keyword, input;

    // skip the first 'argv' as it is the program name
    for (int i = 1; i < argc; i++) {
      keyword = argv[i];

      // NUMBERS
      if (STRUNORMAP_DBL_FOUND(numbers, keyword)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];
  
          if (STRUNORMAP_DBL_FOUND(numbers, input) ||
            STRUNORMAP_STR_FOUND(words, input)
          ) {
            i = j-1;
            break;
          }
          else try {
            numbers[keyword] = std::stod(input);
          }
          catch (...) {
            numbers[keyword] = 0;
          }
        }
      }
      // WORDS
      else if (STRUNORMAP_STR_FOUND(words, keyword)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];

          if (STRUNORMAP_DBL_FOUND(numbers, input) ||
            STRUNORMAP_STR_FOUND(words, input)
          ) {
            i = j-1;
            break;
          }
          else words[keyword] = input;
        }
      }
      // TITLES
      else titles[keyword] = true;
    }
  }

  void CLIParser::assignVector(
    CR_INT argc,
    char *argv[],
    STRUNORMAP_BOL &titles,
    STRUNORMAP<VEC_DBL> &numbers,
    STRUNORMAP<VEC_STR> &words
  ) {
    std::string keyword, input;

    // skip the first 'argv' as it is the program name
    for (int i = 1; i < argc; i++) {
      keyword = argv[i];

      // NUMBERS
      if (STRUNORMAP_FOUND<VEC_DBL>(numbers, keyword)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];
  
          if (STRUNORMAP_FOUND<VEC_DBL>(numbers, input) ||
            STRUNORMAP_FOUND<VEC_STR>(words, input)
          ) {
            i = j-1;
            break;
          }
          else try {
            numbers[keyword].push_back(std::stod(input));
          }
          catch (...) {
            numbers[keyword].push_back(0);
          }
        }
      }
      // WORDS
      else if (STRUNORMAP_FOUND<VEC_STR>(words, keyword)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];

          if (STRUNORMAP_FOUND<VEC_DBL>(numbers, input) ||
            STRUNORMAP_FOUND<VEC_STR>(words, input)
          ) {
            i = j-1;
            break;
          }
          else words[keyword].push_back(input);
        }
      }
      // TITLES
      else titles[keyword] = true;
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_CPP__