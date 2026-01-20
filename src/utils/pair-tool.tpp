#ifndef __MINI_TOOLS__UTILS__PAIR_TOOL_CPP__
#define __MINI_TOOLS__UTILS__PAIR_TOOL_CPP__

namespace mini_tools {
namespace utils {

  template <typename T, typename U>
  VEC_PAIR2<T, U> PairTool<T, U>::mergeVectors(
    CR_VEC<T> &vecA,
    CR_VEC<U> &vecB
  ) {
    VEC_PAIR2<T, U> merged;

    for (int i = 0; i < PairTool<T, U>::getMin(vecA, vecB); i++) {
      merged.push_back({vecA[i], vecB[i]});
    }

    return merged;
  }

  template <typename T, typename U>
  void PairTool<T, U>::unmergeVectors(
    CR_VEC_PAIR2<T, U> merged,
    VEC<T> &vecA,
    VEC<U> &vecB,
    CR_BOL needClear
  ) {
    if (needClear) {
      vecA.clear();
      vecB.clear();
    }

    for (CR_PAIR2<T, U> pair : merged) {
      vecA.push_back(pair.first);
      vecB.push_back(pair.second);
    }
  }

  template <typename T, typename U>
  PAIR2<VEC<T>, VEC<U>> PairTool<T, U>::unmergeVectors(
    CR_VEC_PAIR2<T, U> merged
  ) {
    VEC<T> vecA;
    VEC<U> vecB;

    PairTool<T, U>::unmergeVectors(
      merged, vecA, vecB
    );

    return std::make_pair(vecA, vecB);
  }

  //____________|
  // SIZE TOOLS |
  //____________|

  template <typename T, typename U>
  PAIR_SZ PairTool<T, U>::generateSizes(
    CR_VEC<T> vecA,
    CR_VEC<U> vecB
  ) {
    return std::make_pair(
      vecA.size(), vecB.size()
    );
  }

  template <typename T, typename U>
  PAIR_SZ PairTool<T, U>::generateSizes(
    CR_PAIR2<VEC<T>, VEC<U>> pairVec
  ) {
    return PairTool<T, U>::generateSizes(
      pairVec.first,
      pairVec.second
    );
  }

  template <typename T, typename U>
  size_t PairTool<T, U>::getMin(
    CR_VEC<T> vecA,
    CR_VEC<U> vecB
  ) {
    if (vecA.size() > vecB.size()) {
      return vecB.size();
    }

    return vecA.size();
  }

  template <typename T, typename U>
  size_t PairTool<T, U>::getMin(
    CR_PAIR2<VEC<T>, VEC<U>> pairVec
  ) {
    return PairTool<T, U>::getMin(
      pairVec.first,
      pairVec.second
    );
  }

  template <typename T, typename U>
  size_t PairTool<T, U>::getMax(
    CR_VEC<T> vecA,
    CR_VEC<U> vecB
  ) {
    if (vecA.size() < vecB.size()) {
      return vecB.size();
    }

    return vecA.size();
  }

  template <typename T, typename U>
  size_t PairTool<T, U>::getMax(
    CR_PAIR2<VEC<T>, VEC<U>> pairVec
  ) {
    return PairTool<T, U>::getMax(
      pairVec.first,
      pairVec.second
    );
  }

  template <typename T, typename U>
  PAIR_SZ PairTool<T, U>::getDifferences(
    CR_VEC<T> vecA,
    CR_VEC<U> vecB
  ) {
    const size_t max = PairTool<T, U>::getMax(vecA, vecB);

    return std::make_pair(
      max - vecA.size(),
      max - vecB.size()
    );
  }

  template <typename T, typename U>
  PAIR_SZ PairTool<T, U>::getDifferences(
    CR_PAIR2<VEC<T>, VEC<U>> pairVec
  ) {
    return PairTool<T, U>::getDifferences(
      pairVec.first,
      pairVec.second
    );
  }

  template <typename T, typename U>
  PAIR_LLI PairTool<T, U>::getDifferences(
    CR_VEC<T> vecA,
    CR_VEC<U> vecB,
    CR_LLI targetSz
  ) {
    return std::make_pair(
      targetSz - vecA.size(),
      targetSz - vecB.size()
    );
  }

  template <typename T, typename U>
  PAIR_LLI PairTool<T, U>::getDifferences(
    CR_PAIR2<VEC<T>, VEC<U>> pairVec,
    CR_LLI targetSz
  ) {
    return PairTool<T, U>::getDifferences(
      pairVec.first,
      pairVec.second,
      targetSz
    );
  }

  template <typename T, typename U>
  void PairTool<T, U>::balance(
    VEC<T> &vecA,
    VEC<U> &vecB,
    CR<T> paddingA,
    CR<U> paddingB
  ) {
    PAIR_SZ differences = PairTool<T, U>::getDifferences(vecA, vecB);

    std::vector<T> additions(differences.first, paddingA);
    vecA.reserve(vecA.size() + differences.first);
    vecA.insert(vecA.end(), additions.begin(), additions.end());

    additions = std::vector<T>(differences.second, paddingB);
    vecB.reserve(vecB.size() + differences.second);
    vecB.insert(vecB.end(), additions.begin(), additions.end());
  }

  template <typename T, typename U>
  void PairTool<T, U>::balance(
    PAIR2<VEC<T>, VEC<U>> &pairVec,
    CR_PAIR2<T, U> pairPadding
  ) {
    PairTool<T, U>::balance(
      pairVec.first,
      pairVec.second,
      pairPadding.first,
      pairPadding.second
    );
  }

  template <typename T, typename U>
  void PairTool<T, U>::balance(
    VEC<T> &vecA,
    VEC<U> &vecB,
    CR<T> paddingA,
    CR<U> paddingB,
    LLI targetSz
  ) {
    if (targetSz < 0) targetSz = 0;

    PAIR_LLI differences = PairTool<T, U>::getDifferences(
      vecA, vecB, targetSz
    );

    // vector A
    if (differences.first < 0) {
      vecA = std::vector<T>(
        vecA.begin(), vecA.end() + differences.first
      );
    }
    else if (differences.first > 0) {
      std::vector<T> additions(differences.first, paddingA);
      vecA.reserve(vecA.size() + differences.first);
      vecA.insert(vecA.end(), additions.begin(), additions.end());
    }

    // vector B
    if (differences.second < 0) {
      vecB = std::vector<T>(
        vecB.begin(), vecB.end() + differences.second
      );
    }
    else if (differences.second > 0) {
      std::vector<T> additions(differences.second, paddingB);
      vecB.reserve(vecB.size() + differences.second);
      vecB.insert(vecB.end(), additions.begin(), additions.end());
    }
  }

  template <typename T, typename U>
  void PairTool<T, U>::balance(
    PAIR2<VEC<T>, VEC<U>> &pairVec,
    CR_PAIR2<T, U> pairPadding,
    LLI targetSz
  ) {
    PairTool<T, U>::balance(
      pairVec.first,
      pairVec.second,
      pairPadding.first,
      pairPadding.second,
      targetSz
    );
  }
}}

#endif // __MINI_TOOLS__UTILS__PAIR_TOOL_CPP__