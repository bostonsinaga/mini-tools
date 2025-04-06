#ifndef __MINI_TOOLS__UTILS__PAIR_TOOLS_H__
#define __MINI_TOOLS__UTILS__PAIR_TOOLS_H__

namespace mini_tools {
namespace utils {

  template <class T, class U>
  class PairTools {
  private:
    PairTools() = delete;

  public:
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
      VEC<U> &vecB
    );

    static PAIR2<VEC<T>, VEC<U>> unmergeVectors(
      CR_VEC_PAIR2<T, U> merged
    );

    //____________|
    // SIZE TOOLS |
    //____________|

    static PAIR<size_t> generateSizes(
      CR_VEC<T> &vecA,
      CR_VEC<U> &vecB
    );

    static size_t getMin(
      CR_VEC<T> &vecA,
      CR_VEC<U> &vecB
    );

    static size_t getMax(
      CR_VEC<T> &vecA,
      CR_VEC<U> &vecB
    );

    static PAIR<size_t> getDifferences(
      CR_VEC<T> &vecA,
      CR_VEC<U> &vecB
    );

    static PAIR<LLI> getDifferences(
      CR_VEC<T> &vecA,
      CR_VEC<U> &vecB,
      CR_LLI targetSize
    );

    static void balance(
      VEC<T> &vecA,
      VEC<U> &vecB,
      CR<T> coveringValueA,
      CR<U> coveringValueB
    );

    static void balance(
      VEC<T> &vecA,
      VEC<U> &vecB,
      CR<T> coveringValueA,
      CR<U> coveringValueB,
      LLI targetSize
    );
  };
}}

#include "utils/pair-tools.tpp"
#endif // __MINI_TOOLS__UTILS__PAIR_TOOLS_H__