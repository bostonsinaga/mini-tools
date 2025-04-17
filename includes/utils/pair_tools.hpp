#ifndef __MINI_TOOLS__UTILS__PAIR_TOOLS_HPP__
#define __MINI_TOOLS__UTILS__PAIR_TOOLS_HPP__

namespace mini_tools {
namespace utils {

  template <class T, class U>
  class PairTools final {
  public:
    PairTools() = delete;

    /**
     * Combine two vectors into one vector of pairs.
     * This will ignore any other vector members that exceed the least vector.
     */
    static VEC_PAIR2<T, U> mergeVectors(
      CR_VEC<T> &vecA,
      CR_VEC<U> &vecB
    );

    /**
     * Separate vector of pairs into two vectors.
     */
    static void unmergeVectors(
      CR_VEC_PAIR2<T, U> merged,
      VEC<T> &vecA,
      VEC<U> &vecB,
      CR_BOL needClear = false
    );

    static PAIR2<VEC<T>, VEC<U>> unmergeVectors(
      CR_VEC_PAIR2<T, U> merged
    );

    //____________|
    // SIZE TOOLS |
    //____________|

    static PAIR<size_t> generateSizes(
      CR_VEC<T> vecA,
      CR_VEC<U> vecB
    );

    static PAIR<size_t> generateSizes(
      CR_PAIR2<VEC<T>, VEC<U>> pairVec
    );

    static size_t getMin(
      CR_VEC<T> vecA,
      CR_VEC<U> vecB
    );

    static size_t getMin(
      CR_PAIR2<VEC<T>, VEC<U>> pairVec
    );

    static size_t getMax(
      CR_VEC<T> vecA,
      CR_VEC<U> vecB
    );

    static size_t getMax(
      CR_PAIR2<VEC<T>, VEC<U>> pairVec
    );

    static PAIR<size_t> getDifferences(
      CR_VEC<T> vecA,
      CR_VEC<U> vecB
    );

    static PAIR<size_t> getDifferences(
      CR_PAIR2<VEC<T>, VEC<U>> pairVec
    );

    static PAIR<LLI> getDifferences(
      CR_VEC<T> vecA,
      CR_VEC<U> vecB,
      CR_LLI targetSz
    );

    static PAIR<LLI> getDifferences(
      CR_PAIR2<VEC<T>, VEC<U>> pairVec,
      CR_LLI targetSz
    );

    static void balance(
      VEC<T> &vecA,
      VEC<U> &vecB,
      CR<T> paddingA,
      CR<U> paddingB
    );

    static void balance(
      PAIR2<VEC<T>, VEC<U>> &pairVec,
      CR_PAIR2<T, U> pairPadding
    );

    static void balance(
      VEC<T> &vecA,
      VEC<U> &vecB,
      CR<T> paddingA,
      CR<U> paddingB,
      LLI targetSz
    );

    static void balance(
      PAIR2<VEC<T>, VEC<U>> &pairVec,
      CR_PAIR2<T, U> pairPadding,
      LLI targetSz
    );
  };
}}

#include "utils/pair_tools.tpp"
#endif // __MINI_TOOLS__UTILS__PAIR_TOOLS_HPP__