#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__

#include "../algorithms/calculators.h"

namespace mini_tools {
namespace utils {

  template <typename T>
  bool VecTools<T>::hasIndex(VEC<T> &vec, CR_INT idx) {
    if (idx < vec.size() && idx >= 0) return true;
    return false;
  }

  template <typename T>
  bool VecTools<T>::hasIndexes(VEC<T> &vec, CR_VEC_INT idxs) {
    for (CR_INT i : idxs) {
      if (!hasIndex(vec, i)) return false;
    }
    return idxs.size() > 0 ? true : false;
  }

  template <typename T>
  LLI VecTools<T>::getIndex(
    VEC<T> &vec,
    CR<T> data,
    EQUAL_RULE equalRule
  ) {
    for (int i = 0; i < vec.size(); i++) {
      if (data == vec[i] || equalRule(data, vec[i])) return i;
    }
    return -1;
  }

  template <typename T>
  T VecTools<T>::getAt(VEC<T> &vec, CR_INT idx, CR<T> defaultReturn) {
    if (VecTools<T>::hasIndex(vec, idx)) return vec[idx];
    return defaultReturn;
  }

  template <typename T>
  void VecTools<T>::concat(
    VEC<T> &targetVec,
    CR_VEC<T> additionVec
  ) {
    targetVec.reserve(targetVec.size() + additionVec.size());
    targetVec.insert(targetVec.end(), additionVec.begin(), additionVec.end());
  }

  template <typename T>
  VEC<T> VecTools<T>::join(
    CR_VEC<T> vecA,
    CR_VEC<T> vecB
  ) {
    VEC<T> newVec;
    VecTools<T>::concat(newVec, vecA);
    VecTools<T>::concat(newVec, vecB);
    return newVec;
  }

  template <typename T>
  void VecTools<T>::cutInterval(
    VEC<T> &vec,
    VEC<T> &wasted,
    int begin, int end,
    CR_BOL onlyWasted,
    CR_BOL validatingIndex
  ) {
    if (vec.empty()) return;

    // slower
    if (validatingIndex) {

      // bad interval
      if ((begin < 0 && end < 0) ||
        (begin >= vec.size() && end >= vec.size())
      ) { return; }

      VecTools<T>::fixIndexInterval(vec, begin, end);
    }

    // separated
    wasted = VEC<T>(vec.begin() + begin, vec.begin() + end + 1);

    // change the original
    if (!onlyWasted) {
      vec = VecTools<T>::join(
        VEC<T>(vec.begin(), vec.begin() + begin),
        VEC<T>(vec.begin() + end + 1, vec.end())
      );
    }
  }

  template <typename T>
  VEC<T> VecTools<T>::cutInterval(
    VEC<T> &vec,
    CR_INT begin, CR_INT end,
    CR_BOL onlyWasted,
    CR_BOL validatingIndex
  ) {
    VEC<T> wasted;

    VecTools<T>::cutInterval(
      vec, wasted,
      begin, end,
      onlyWasted, validatingIndex
    );

    return wasted;
  }

  template <typename T>
  void VecTools<T>::cutSingle(
    VEC<T> &vec,
    T &wasted,
    int idx,
    CR_BOL onlyWasted,
    CR_BOL validatingIndex
  ) {
    if (vec.empty()) return;

    // slower
    if (validatingIndex) {
      if (idx < 0) idx = 0;
      else if (idx >= vec.size()) idx = vec.size() - 1;
    }

    // separated
    wasted = vec[idx];

    // change the original
    if (!onlyWasted) {
      vec = VecTools<T>::join(
        VEC<T>(vec.begin(), vec.begin() + idx),
        VEC<T>(vec.begin() + idx + 1, vec.end())
      );
    }
  }

  template <typename T>
  T VecTools<T>::cutSingle(
    VEC<T> &vec,
    CR_INT idx,
    CR_BOL onlyWasted,
    CR_BOL validatingIndex
  ) {
    T wasted = vec[idx];

    VecTools<T>::cutSingle(
      vec, wasted,
      idx, onlyWasted,
      validatingIndex
    );

    return wasted;
  }

  template <typename T>
  void VecTools<T>::cutIndexes(
    VEC<T> &vec,
    VEC<T> &wasted,
    VEC_INT idxs,
    CR_BOL lockedIndex,
    CR_BOL onlyWasted,
    CR_BOL validatingIndex,
    CR_BOL removingExceededIndexes
  ) {
    if (vec.empty()) return;

    // ascending
    if (algorithms::Calc::isArithmeticSequence(idxs, 1)) {
      VecTools<T>::cutInterval(
        vec, wasted,
        idxs[0], idxs[idxs.size() - 1],
        onlyWasted, validatingIndex
      );
    }
    // descending
    else if (algorithms::Calc::isArithmeticSequence(idxs, -1)) {
      VecTools<T>::cutInterval(
        vec, wasted,
        idxs[idxs.size() - 1], idxs[0],
        onlyWasted, validatingIndex
      );
    }
    // one by one
    else {
      // slower
      if (validatingIndex) {
        VecTools<T>::fixIndexes(vec, idxs, removingExceededIndexes);
      }

      for (int i = 0; i < idxs.size(); i++) {

        wasted.push_back(VecTools<T>::cutSingle(
          vec, idxs[i], onlyWasted, validatingIndex
        ));

        if (lockedIndex) {
          for (int j = i+1; j < idxs.size(); j++) {
            if (idxs[i] < idxs[j]) idxs[j]--;
          }
        }
      }
    }
  }

  template <typename T>
  VEC<T> VecTools<T>::cutIndexes(
    VEC<T> &vec,
    CR_VEC_INT idxs,
    CR_BOL lockedIndex,
    CR_BOL onlyWasted,
    CR_BOL validatingIndex,
    CR_BOL removingExceededIndexes
  ) {
    VEC<T> wasted;

    VecTools<T>::cutIndexes(
      vec, wasted,
      idxs, lockedIndex,
      onlyWasted, validatingIndex,
      removingExceededIndexes
    );

    return wasted;
  }

  template <typename T>
  std::tuple<VEC<T>, VEC<T>> VecTools<T>::cleanDuplicateInside(
    VEC<T> &vec,
    CR_BOL originalAscending,
    EQUAL_RULE equalRule
  ) {
    std::tuple<VEC<T>, VEC<T>> wastedTuple({}, {});

    static std::function<bool(
      CR<T>&, CR<T>&, CR_UI
    )> lambda = [&](
      CR<T> &a, CR<T> &b, CR_UI cutIdx
    )->bool {
      // equal based on pointer
      if constexpr (std::is_pointer<T>::value) {
        if (a == b) {
          std::get<0>(wastedTuple).push_back(VecTools<T>::cutSingle(vec, cutIdx));
          return true;
        }
      }
      else { // equal based on value
        if (a == b || equalRule(a, b)) {
          std::get<1>(wastedTuple).push_back(VecTools<T>::cutSingle(vec, cutIdx));
          return true;
        }
      }
      return false;
    };

    if (originalAscending) {
      for (int i = 0; i < vec.size() - 1; i++) {
        for (int j = i+1; j < vec.size(); j++) {
          if (lambda(vec[i], vec[j], j)) j--;
        }
      }
    }
    else for (int i = vec.size() - 1; i > 0; i--) {
      for (int j = i - 1; j >= 0; j--) {
        if (lambda(vec[i], vec[j], j)) i--;
      }
    }

    return wastedTuple;
  }

  template <typename T>
  std::tuple<VEC<T>, VEC<T>> VecTools<T>::cleanDuplicateToMember(
    VEC<T> &vec, CR<T> mem,
    CR_BOL originalAscending,
    EQUAL_RULE equalRule
  ) {
    std::tuple<VEC<T>, VEC<T>> wastedTuple({}, {});
    bool firstIgnored = false;

    static std::function<bool(
      CR<T>&, CR<T>&, CR_UI
    )> lambda = [&](
      CR<T> &a, CR<T> &b, CR_UI cutIdx
    )->bool {
      // equal based on pointer
      if constexpr (std::is_pointer<T>::value) {
        if (a == b) {
          if (firstIgnored) {
            std::get<0>(wastedTuple).push_back(VecTools<T>::cutSingle(vec, cutIdx));
            return true;
          }
          else firstIgnored = true;
        }
      }
      else { // equal based on value
        if (a == b || equalRule(a, b)) {
          if (firstIgnored) {
            std::get<1>(wastedTuple).push_back(VecTools<T>::cutSingle(vec, cutIdx));
            return true;
          }
          else firstIgnored = true;
        }
      }
      return false;
    };

    if (originalAscending) {
      for (int i = 0; i < vec.size(); i++) {
        if (lambda(mem, vec[i], i)) i--;
      }
    }
    else for (int i = vec.size() - 1; i >= 0; i--) {
      lambda(mem, vec[i], i);
    }

    return wastedTuple;
  }

  template <typename T>
  void VecTools<T>::fixIndexes(
    VEC<T> &vec,
    VEC_INT &idxs,
    CR_BOL removed
  ) {
    if (vec.empty()) return;

    for (int i = 0; i < idxs.size(); i++) {
      if (!VecTools<T>::hasIndex(vec, idxs[i])) {
        if (removed) {
          VecTools<int>::cutSingle(idxs, i);
          i--;
        }
        else {
          if (idxs[i] < 0) idxs[i] = 0;
          else if (idxs[i] >= vec.size()) idxs[i] = vec.size() - 1;
        }
      }
    }
  }

  template <typename T>
  void VecTools<T>::fixIndexInterval(VEC<T> &vec, int &begin, int &end) {
    if (begin > end) std::swap(begin, end);
    if (begin < 0 || begin > vec.size()) begin = 0;
    if (end <= 0 || end >= vec.size()) end = vec.size() - 1;
  }

  template <typename T>
  bool VecTools<T>::isIndexIntervalValid(VEC<T> &vec, CR_INT begin, CR_INT end) {
    if (begin < end &&
      begin >= 0 && begin < vec.size() - 1 &&
      end > 0 && end < vec.size()
    ) { return true; }
    return false;
  }

  template <typename T>
  VEC<T> VecTools<T>::collapse(CR_VEC2<T> vec) {
    VEC<T> reduction;

    for (CR_VEC<T> red: vec) {
      VecTools<T>::concat(reduction, red);
    }

    return reduction;
  }
}}

#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__