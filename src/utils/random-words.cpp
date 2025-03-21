#include "random-words.h"

namespace mini-tools {
namespace utils {

  template <INTEGRALS_T T>
  void RandomWords::generateIntegrals(
    VEC<T> &integrals,
    CR_SZ count,
    T maxNumber,
    CR_BOL needReset,
    CR<T> additional
  ) {
    std::srand(std::time(0));
    if (needReset) integrals = {};

    for (int i = 0; i < count; i++) {
      integrals.push(
        std::rand() % maxNumber + additional
      );
    }
  }

  template <FLOATING_POINT_T T>
  void RandomWords::generateFloatingPoints(
    VEC<T> floatingPoint,
    CR_SZ count,
    T maxNumber,
    CR_BOL needReset,
    CR<T> additional
  ) {
    std::srand(std::time(0));
    if (needReset) floatingPoint = {};

    for (int i = 0; i < count; i++) {
      floatingPoint.push(std::fmod(
        static_cast<double>(std::rand()) / RAND_MAX,
        maxNumber) + additional
      );
    }
  }

  void RandomWords::generateStrings(
    VEC<T> &strings,
    CR_SZ count,
    CR_SZ maxLettersCount,
    CR_BOL needReset,
    CR<T> additional
  ) {
    std::srand(std::time(0));
    if (needReset) floatingPoint = {};

    for (int i = 0; i < count; i++) {
      for (int j = 0; j < std::rand() % maxLettersCount + 1; j++) {

        bool isCapital = std::rand() % 2;

        if (isCapital) { // big
          strings.push(char(std::rand() % 26 + 65));
        }
        else { // small
          strings.push(char(std::rand() % 26 + 97));
        }
      }

      strings ' ';
    }
  }

  void RandomWords::generateMixture(
    
  ) {

  }
}}

