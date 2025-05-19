#ifndef __MINI_TOOLS__UTILS__RANDOM_WORDS_HPP__
#define __MINI_TOOLS__UTILS__RANDOM_WORDS_HPP__

namespace mini_tools {
namespace utils {

  class RandomWords final {
  private:
    // default 0-1000
    static PAIR_LD rouletteInterval;

    static std::random_device randomDevice;
    static std::mt19937 mersenneTwister;
    static std::uniform_int_distribution<LLI> distributeInteger;
    static std::uniform_real_distribution<LD> distributeReal;

  /** Half-open intervals [a, b) */
  public:
    RandomWords() = delete;

    static void setRouletteInterval(
      CR_LD begin, CR_LD end
    );

    static void updateDistributeIntegerInterval();
    static void updateDistributeRealInterval();

    static void setDistributeIntegerInterval(
      CR_LLI begin, CR_LLI end
    );

    static void setDistributeRealInterval(
      CR_LD begin, CR_LD end
    );

    /** Call these to get a random number */

    static LLI rouletteInteger() {
      return distributeInteger(mersenneTwister);
    }

    static LD rouletteReal() {
      return distributeReal(mersenneTwister);
    }

    /** The Random Words */

    template <std::integral T>
    static VEC<T> generateIntegrals(
      CR_SZ count,
      T maxNumber,
      CR<T> additional
    );

    template <std::floating_point T>
    static VEC<T> generateFloatingPoints(
      CR_SZ count,
      T maxNumber,
      CR<T> additional
    );

    static VEC_STR generateStrings(
      CR_SZ count,
      // first is minimum, second -1 is maximum
      PAIR_LLI lengthInterval,
      CR_BOL lettersOnly,
      CR_BOL alwaysStartWithLetter
    );
  };
}}

#include "utils/random-words.tpp"
#endif // __MINI_TOOLS__UTILS__RANDOM_WORDS_HPP__