#ifndef __MINI_TOOLS__UTILS__RANDOM_WORDS_CPP__
#define __MINI_TOOLS__UTILS__RANDOM_WORDS_CPP__

#include "types.h"
#include "utils/random-words.h"

namespace mini_tools {
namespace utils {

  /** VARIABLES */

  PAIR<LD> RandomWords::rouletteInterval {0, 1000};
  std::random_device RandomWords::randomDevice;
  std::mt19937 RandomWords::mersenneTwister(RandomWords::randomDevice());

  std::uniform_int_distribution<LLI> RandomWords::distributeInteger(
    RandomWords::rouletteInterval.first,
    RandomWords::rouletteInterval.second
  );

  std::uniform_real_distribution<LD> RandomWords::distributeReal(
    RandomWords::rouletteInterval.first,
    RandomWords::rouletteInterval.second
  );

  /** METHODS */

  void RandomWords::setRouletteInterval(
    CR_LD begin, CR_LD end
  ) {
    if (begin > end) RandomWords::rouletteInterval = {end, begin};
    else RandomWords::rouletteInterval = {begin, end};
  }

  void RandomWords::updateDistributeIntegerInterval() {
    distributeInteger.param(std::uniform_int_distribution<LLI>::param_type(
      RandomWords::rouletteInterval.first,
      RandomWords::rouletteInterval.second
    ));
  }

  void RandomWords::updateDistributeRealInterval() {
    distributeReal.param(std::uniform_real_distribution<LD>::param_type(
      RandomWords::rouletteInterval.first,
      RandomWords::rouletteInterval.second
    ));
  }

  void RandomWords::setDistributeIntegerInterval(
    CR_LLI begin, CR_LLI end
  ) {
    setRouletteInterval(begin, end);
    updateDistributeIntegerInterval();
  }

  void RandomWords::setDistributeRealInterval(
    CR_LD begin, CR_LD end
  ) {
    setRouletteInterval(begin, end);
    updateDistributeRealInterval();
  }

  VEC_STR RandomWords::generateStrings(
    CR_SZ count,
    PAIR<LLI> lengthInterval,
    CR_BOL lettersOnly,
    bool alwaysStartWithLetter
  ) {
    VEC_STR strings;
    std::string word;

    LLI last;
    SI selected;
    const SI division = 3 - lettersOnly;

    // the lengths are always positive numbers
    lengthInterval.first = std::abs(lengthInterval.first);
    lengthInterval.second = std::abs(lengthInterval.second);

    // the first length is always smaller
    if (lengthInterval.first > lengthInterval.second) {
      std::swap(lengthInterval.first, lengthInterval.second);
    }

    // avoid dividing by zero (cancel)
    if (lengthInterval.second == 0) return {};

    // pushing the 'word' to the 'strings'
    for (size_t i = 0; i < count; i++) {

      // random length with minimum value as the first length
      last = RandomWords::rouletteInteger()
        % lengthInterval.second + lengthInterval.first;

      // generating the 'word'
      for (LLI j = lengthInterval.first; j < last; j++) {

        switch (selected) {
          case 0: { // uppercase
            word.push_back(char(
              RandomWords::rouletteInteger() % 26 + 65
            ));
          break;}
          case 1: { // lowercase
            word.push_back(char(
              RandomWords::rouletteInteger() % 26 + 97
            ));
          break;}
          case 2: { // integer
            // repeat with next as letter
            if (alwaysStartWithLetter) {
              j--;
              alwaysStartWithLetter = false;
              selected = RandomWords::rouletteInteger() % 2;
              continue;
            }
            // number
            else word.push_back(char(
              RandomWords::rouletteInteger() % 10 + 48
            ));
          break;}
        }

        // up to 3 possible values
        selected = RandomWords::rouletteInteger() % division;
      }

      // push and reset the 'word'
      if (last) {
        strings.push_back(word);
        word = "";
      }
    }

    return std::move(strings);
  }
}}

#endif // __MINI_TOOLS__UTILS__RANDOM_WORDS_CPP__