#ifndef __MINI_TOOLS__UTILS__PAIR_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__PAIR_TOOLS_CPP__

namespace mini_tools {
namespace utils {

  template <typename T, typename U>
  VEC_PAIR2<T, U> PairTools<T, U>::mergeVectors(
    CR_VEC<T> &vecA,
    CR_VEC<U> &vecB
  ) {
    VEC_PAIR2<T, U> merged;

    for (int i = 0; i < PairTools<T, U>::getMin(vecA, vecB); i++) {
      merged.push_back({vecA[i], vecB[i]});
    }

    return merged;
  }

  template <typename T, typename U>
  void PairTools<T, U>::unmergeVectors(
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
  PAIR2<VEC<T>, VEC<U>> PairTools<T, U>::unmergeVectors(
    CR_VEC_PAIR2<T, U> merged
  ) {
    VEC<T> vecA;
    VEC<U> vecB;

    PairTools<T, U>::unmergeVectors(
      merged, vecA, vecB
    );

    return std::make_pair(vecA, vecB);
  }

  //____________|
  // SIZE TOOLS |
  //____________|

  template <typename T, typename U>
  PAIR<size_t> PairTools<T, U>::generateSizes(
    CR_VEC<T> &vecA,
    CR_VEC<U> &vecB
  ) {
    return std::make_pair(
      vecA.size(), vecB.size()
    );
  }

  template <typename T, typename U>
  size_t PairTools<T, U>::getMin(
    CR_VEC<T> &vecA,
    CR_VEC<U> &vecB
  ) {
    if (vecA.size() > vecB.size()) {
      return vecB.size();
    }

    return vecA.size();
  }

  template <typename T, typename U>
  size_t PairTools<T, U>::getMax(
    CR_VEC<T> &vecA,
    CR_VEC<U> &vecB
  ) {
    if (vecA.size() < vecB.size()) {
      return vecB.size();
    }

    return vecA.size();
  }

  template <typename T, typename U>
  PAIR<size_t> PairTools<T, U>::getDifferences(
    CR_VEC<T> &vecA,
    CR_VEC<U> &vecB
  ) {
    const size_t max = PairTools<T, U>::getMax(vecA, vecB);

    return std::make_pair(
      max - vecA.size(),
      max - vecB.size()
    );
  }

  template <typename T, typename U>
  PAIR<LLI> PairTools<T, U>::getDifferences(
    CR_VEC<T> &vecA,
    CR_VEC<U> &vecB,
    CR_LLI targetSize
  ) {
    return std::make_pair(
      targetSize - vecA.size(),
      targetSize - vecB.size()
    );
  }

  template <typename T, typename U>
  void PairTools<T, U>::balance(
    VEC<T> &vecA,
    VEC<U> &vecB,
    CR<T> coveringValueA,
    CR<U> coveringValueB
  ) {
    PAIR<size_t> differences = PairTools<T, U>::getDifferences(vecA, vecB);

    std::vector<T> additions(differences.first, coveringValueA);
    vecA.reserve(vecA.size() + differences.first);
    vecA.insert(vecA.end(), additions.begin(), additions.end());

    additions = std::vector<T>(differences.second, coveringValueB);
    vecB.reserve(vecB.size() + differences.second);
    vecB.insert(vecB.end(), additions.begin(), additions.end());
  }

  template <typename T, typename U>
  void PairTools<T, U>::balance(
    VEC<T> &vecA,
    VEC<U> &vecB,
    CR<T> coveringValueA,
    CR<U> coveringValueB,
    LLI targetSize
  ) {
    if (targetSize < 0) targetSize = 0;

    PAIR<LLI> differences = PairTools<T, U>::getDifferences(
      vecA, vecB, targetSize
    );

    // vector A
    if (differences.first < 0) {
      vecA = std::vector<T>(
        vecA.begin(), vecA.end() + differences.first
      );
    }
    else if (differences.first > 0) {
      std::vector<T> additions(differences.first, coveringValueA);
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
      std::vector<T> additions(differences.second, coveringValueB);
      vecB.reserve(vecB.size() + differences.second);
      vecB.insert(vecB.end(), additions.begin(), additions.end());
    }
  }
}}

#endif // __MINI_TOOLS__UTILS__PAIR_TOOLS_CPP__