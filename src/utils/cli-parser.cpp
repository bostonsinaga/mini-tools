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
    std::string param, input;

    // skip the first 'argv' as it is the program name
    for (int i = 1; i < argc; i++) {
      param = argv[i];

      // NUMBERS
      if (STRUNORMAP_DBL_FOUND(numbers, param)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];
  
          if (STRUNORMAP_DBL_FOUND(numbers, input) ||
            STRUNORMAP_STR_FOUND(words, input)
          ) {
            i = j-1;
            break;
          }
          else try {
            numbers[param] = std::stod(input);
          }
          catch (...) {
            numbers[param] = 0;
          }
        }
      }
      // WORDS
      else if (STRUNORMAP_STR_FOUND(words, param)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];

          if (STRUNORMAP_DBL_FOUND(numbers, input) ||
            STRUNORMAP_STR_FOUND(words, input)
          ) {
            i = j-1;
            break;
          }
          else words[param] = input;
        }
      }
      // TITLES
      else titles[param] = true;
    }
  }

  void CLIParser::assignVector(
    CR_INT argc,
    char *argv[],
    STRUNORMAP_BOL &titles,
    STRUNORMAP<VEC_DBL> &numbers,
    STRUNORMAP<VEC_STR> &words
  ) {
    std::string param, input;

    // skip the first 'argv' as it is the program name
    for (int i = 1; i < argc; i++) {
      param = argv[i];

      // NUMBERS
      if (STRUNORMAP_FOUND<VEC_DBL>(numbers, param)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];
  
          if (STRUNORMAP_FOUND<VEC_DBL>(numbers, input) ||
            STRUNORMAP_FOUND<VEC_STR>(words, input)
          ) {
            i = j-1;
            break;
          }
          else try {
            numbers[param].push_back(std::stod(input));
          }
          catch (...) {
            numbers[param].push_back(0);
          }
        }
      }
      // WORDS
      else if (STRUNORMAP_FOUND<VEC_STR>(words, param)) {

        for (int j = i+1; j < argc; j++) {
          input = argv[j];

          if (STRUNORMAP_FOUND<VEC_DBL>(numbers, input) ||
            STRUNORMAP_FOUND<VEC_STR>(words, input)
          ) {
            i = j-1;
            break;
          }
          else words[param].push_back(input);
        }
      }
      // TITLES
      else titles[param] = true;
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_CPP__