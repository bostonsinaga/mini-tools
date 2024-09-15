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
  LLI VecTools<T>::getIndex(VEC<T> &vec, CR<T> data) {
    for (int i = 0; i < vec.size(); i++) {
      if (data == vec[i]) return i;
    }
    return -1;
  }

  template <typename T>
  T VecTools<T>::getAt(VEC<T> &vec, CR_INT idx, CR<T> defaultReturn) {
    if (VecTools<T>::hasIndex(vec, idx)) return vec.at(idx);
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
    CR_BOL onlyWasted
  ) {
    int sz = vec.size();

    // bad interval
    if (sz == 0 || 
      (begin < 0 && end < 0) ||
      (begin >= sz && end >= sz)
    ) { return; }

    // inverted interval
    if (begin > end) {
      int buff = begin;
      begin = end;
      end = buff;
    }

    // exceeded interval
    if (begin < 0) begin = 0;
    if (end >= sz) end = sz - 1;

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
    CR_BOL onlyWasted
  ) {
    VEC<T> wasted;
    VecTools<T>::cutInterval(vec, wasted, begin, end, onlyWasted);
    return wasted;
  }

  template <typename T>
  void VecTools<T>::cutSingle(
    VEC<T> &vec,
    T &wasted,
    int idx,
    CR_BOL onlyWasted
  ) {
    if (vec.size() == 0) return;

    if (idx < 0) idx = 0;
    else if (idx >= vec.size()) idx = vec.size() - 1;

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
    CR_BOL onlyWasted
  ) {
    T wasted = vec[idx];
    VecTools<T>::cutSingle(vec, wasted, idx, onlyWasted);
    return wasted;
  }

  template <typename T>
  void VecTools<T>::cutIndexes(
    VEC<T> &vec,
    VEC<T> &wasted,
    VEC_INT idxs,
    CR_BOL lockedIndex,
    CR_BOL onlyWasted
  ) {
    if (vec.size() == 0) return;
    int last = idxs.size() - 1;

    // ascending
    if (algorithms::Calc::isArithmeticSequence(idxs, 1)) {
      VecTools<T>::cutInterval(vec, wasted, idxs[0], idxs[last], onlyWasted);
    }
    // descending
    else if (algorithms::Calc::isArithmeticSequence(idxs, -1)) {
      VecTools<T>::cutInterval(vec, wasted, idxs[last], idxs[0], onlyWasted);
    }
    // one by one
    else {
      wasted = {};
      bool prevIndex = -1;

      for (int i = 0; i < idxs.size(); i++) {

        if (!lockedIndex || (prevIndex >= 0 && prevIndex != idxs[i])) {
          wasted.push_back(VecTools<T>::cutSingle(vec, idxs[i], onlyWasted));
        }

        if (lockedIndex) {
          prevIndex = idxs[i];

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
    VEC_INT idxs,
    CR_BOL lockedIndex,
    CR_BOL onlyWasted
  ) {
    VEC<T> wasted;
    VecTools<T>::cutIndexes(vec, wasted, idxs, lockedIndex, onlyWasted);
    return wasted;
  }

  template <typename T>
  VEC<T> VecTools<T>::cleanDuplicateInside(
    VEC<T> &vec,
    CR_BOL originalAscending,
    EQUAL_RULE equalRule
  ) {
    VEC<T> wastedVec;

    static std::function<bool(
      CR<T>&, CR<T>&, CR_UI
    )> lambda = [&](
      CR<T> &a, CR<T> &b, CR_UI cutIdx
    )->bool {
      if (a == b || equalRule(a, b)) {
        wastedVec.push_back(VecTools<T>::cutSingle(vec, cutIdx));
        return true;
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

    return wastedVec;
  }

  template <typename T>
  VEC<T> VecTools<T>::cleanDuplicateToMember(
    VEC<T> &vec, CR<T> mem,
    CR_BOL originalAscending,
    EQUAL_RULE equalRule
  ) {
    VEC<T> wastedVec;
    bool firstIgnored = false;

    static std::function<bool(
      CR<T>&, CR<T>&, CR_UI
    )> lambda = [&](
      CR<T> &a, CR<T> &b, CR_UI cutIdx
    )->bool {
      if (a == b || equalRule(a, b)) {
        if (firstIgnored) {
          wastedVec.push_back(VecTools<T>::cutSingle(vec, cutIdx));
          return true;
        }
        else firstIgnored = true;
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

    return wastedVec;
  }

  template <typename T>
  void VecTools<T>::fixIndexInterval(int &begin, int &end, T &vec) {
    if (begin > end) std::swap(begin, end);
    if (begin < 0 || begin > vec.size()) begin = 0;
    if (end < 0 || end > vec.size()) end = vec.size();
  }

  template <typename T>
  bool VecTools<T>::isIndexIntervalValid(CR_INT begin, CR_INT end, T &vec) {
    if (begin < end &&
      begin >= 0 && begin <= vec.size() &&
      end >= 0 || end <= vec.size()
    ) { return true; }
    return false;
  }

  template <typename T>
  VEC<T> VecTools<T>::collapse(VEC2<T> vec) {
    VEC<T> reduction;

    for (VEC<T> &red: vec) {
      VecTools<T>::concat(reduction, red);
    }

    return reduction;
  }
}}

#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__