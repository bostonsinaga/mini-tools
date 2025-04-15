#ifndef __MINI_TOOLS__UTILS__RANDOM_WORDS_CPP__
#define __MINI_TOOLS__UTILS__RANDOM_WORDS_CPP__

#include "types.hpp"
#include "utils/random_words.hpp"

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
    CR_BOL alwaysStartWithLetter
  ) {
    VEC_STR strings;
    std::string word;

    enum {uppercase_e, lowercase_e, integer_e};

    LLI last;
    const SI division = 3 - lettersOnly;
    SI selected = RandomWords::rouletteInteger() % division;

    // will change in loop 'j' but be reassigned in loop 'i'
    bool needStartWithLetter = alwaysStartWithLetter;

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

      // second length -1 as the maximum number of characters
      last = RandomWords::rouletteInteger()
        % lengthInterval.second;

      // first length as the minimum number of characters
      if (last < lengthInterval.first) {
        last = lengthInterval.first;
      }

      // generating the 'word'
      for (LLI j = 0; j < last; j++) {

        // uppercase
        if (selected == uppercase_e) {
          word.push_back(char(
            RandomWords::rouletteInteger() % 26 + 65
          ));
        }
        // lowercase
        else if (selected == lowercase_e) {
          word.push_back(char(
            RandomWords::rouletteInteger() % 26 + 97
          ));
        }
        // integer
        else if (selected == integer_e) {

          // repeat with next as letter
          if (needStartWithLetter) {
            j--;
            needStartWithLetter = false;
            selected = RandomWords::rouletteInteger() % 2;
            continue;
          }
          // allowed number
          else word.push_back(char(
            RandomWords::rouletteInteger() % 10 + 48
          ));
        }

        // up to 3 possible values
        selected = RandomWords::rouletteInteger() % division;
      }

      // keep all 'strings' to follow the option
      needStartWithLetter = alwaysStartWithLetter;

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