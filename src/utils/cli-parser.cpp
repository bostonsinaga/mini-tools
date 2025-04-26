#ifndef __MINI_TOOLS__UTILS__CLI_PARSER_CPP__
#define __MINI_TOOLS__UTILS__CLI_PARSER_CPP__

#include "types.hpp"
#include "utils/cli-parser.hpp"

namespace mini_tools {
namespace utils {

  CLIParser::CLIParser(
    CR_INT argc,
    char *argv[],
    CR_VEC_STR numberKeywords,
    CR_VEC_STR wordKeywords
  ) {
    // skip the first 'argv' as it is the program name
    for (int i = 1; i < argc; i++) {
      raws.push_back(argv[i]);
    }

    for (CR_STR key : numberKeywords) {
      latestNumber[key] = 0;
      numberVectors[key] = {};
    }

    for (CR_STR key : wordKeywords) {
      latestWord[key] = "";
      wordVectors[key] = {};
    }
  }

  inline bool CLIParser::isLatestKeyword(CR_STR test) {
    return STRUNORMAP_DBL_FOUND(latestNumber, test) ||
      STRUNORMAP_STR_FOUND(latestWord, test);
  }

  inline bool CLIParser::isVectorKeyword(CR_STR test) {
    return STRUNORMAP_FOUND<VEC_DBL>(numberVectors, test) ||
      STRUNORMAP_FOUND<VEC_STR>(wordVectors, test);
  }

  void CLIParser::assignLatest() {
    for (int i = 0; i < raws.size(); i++) {

      // NUMBERS
      if (STRUNORMAP_DBL_FOUND(latestNumber, raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {
          if (isLatestKeyword(raws[j])) {
            i = j-1;
            break;
          }
          else try {
            latestNumber[raws[i]] = std::stod(raws[j]);
          }
          catch (...) {
            latestNumber[raws[i]] = 0;
          }
        }
      }
      // WORDS
      else if (STRUNORMAP_STR_FOUND(latestWord, raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {
          if (isLatestKeyword(raws[j])) {
            i = j-1;
            break;
          }
          else latestWord[raws[i]] = raws[j];
        }
      }
      // TITLES
      else titles[raws[i]] = true;
    }
  }

  void CLIParser::assignVectors() {
    for (int i = 0; i < raws.size(); i++) {

      // NUMBERS
      if (STRUNORMAP_FOUND<VEC_DBL>(numberVectors, raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {
          if (isVectorKeyword(raws[j])) {
            i = j-1;
            break;
          }
          else try {
            numberVectors[raws[i]].push_back(std::stod(raws[j]));
          }
          catch (...) {
            numberVectors[raws[i]].push_back(0);
          }
        }
      }
      // WORDS
      else if (STRUNORMAP_FOUND<VEC_STR>(wordVectors, raws[i])) {

        for (int j = i+1; j < raws.size(); j++) {
          if (isVectorKeyword(raws[j])) {
            i = j-1;
            break;
          }
          else wordVectors[raws[i]].push_back(raws[j]);
        }
      }
      // TITLES
      else titles[raws[i]] = true;
    }
  }

  bool CLIParser::hasTitle(CR_STR keyword) {

    if (STRUNORMAP_BOL_FOUND(titles, keyword)) {
      return titles[keyword];
    }

    return false;
  }

  VEC_STR CLIParser::extractTitles() {
    VEC_STR keywords;

    for (CR_PAIR2<CR_STR, CR_BOL> pair : titles) {
      keywords.push_back(pair.first);
    }

    return keywords;
  }

  double CLIParser::getLatestNumber(CR_STR keyword) {

    if (STRUNORMAP_DBL_FOUND(latestNumber, keyword)) {
      return latestNumber[keyword];
    }

    return 0;
  }

  std::string CLIParser::getLatestWord(CR_STR keyword) {

    if (STRUNORMAP_STR_FOUND(latestWord, keyword)) {
      return latestWord[keyword];
    }

    return "";
  }

  VEC_DBL CLIParser::getVectorNumber(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_DBL>(numberVectors, keyword)) {
      return numberVectors[keyword];
    }

    return {};
  }

  VEC_STR CLIParser::getVectorWord(CR_STR keyword) {

    if (STRUNORMAP_FOUND<VEC_STR>(wordVectors, keyword)) {
      return wordVectors[keyword];
    }

    return {};
  }
}}

#endif // __MINI_TOOLS__UTILS__CLI_PARSER_CPP__