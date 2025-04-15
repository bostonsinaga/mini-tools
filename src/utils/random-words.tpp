#ifndef __MINI_TOOLS__UTILS__RANDOM_WORDS_TPP__
#define __MINI_TOOLS__UTILS__RANDOM_WORDS_TPP__

namespace mini_tools {
namespace utils {

  template <std::integral T>
  VEC<T> RandomWords::generateIntegrals(
    CR_SZ count,
    T maxNumber,
    CR<T> additional
  ) {
    VEC<T> integrals;

    for (int i = 0; i < count; i++) {
      integrals.push_back(
        std::rand() % maxNumber + additional
      );
    }

    return std::move(integrals);
  }

  template <std::floating_point T>
  VEC<T> RandomWords::generateFloatingPoints(
    CR_SZ count,
    T maxNumber,
    CR<T> additional
  ) {
    VEC<T> floatingPoints;

    for (int i = 0; i < count; i++) {
      floatingPoints.push_back(std::fmod(
        static_cast<double>(std::rand()) / RAND_MAX,
        maxNumber) + additional
      );
    }

    return std::move(floatingPoints);
  }
}}

#endif // __MINI_TOOLS__UTILS__RANDOM_WORDS_TPP__