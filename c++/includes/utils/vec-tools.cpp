#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__

#include "../algorithms/calculators.h"

namespace mini_tools {
namespace utils {

  template <typename T>
  bool VecTools<T>::isIndexOf(std::vector<T> &vec, int idx) {
    if (idx < vec->size() && idx >= 0) return true;
    return false;
  }

  template <typename T>
  T VecTools<T>::getIndexOf(std::vector<T> &vec, int idx, T defaultReturn) {
    if (VecTools<T>::isIndexOf(vec, idx)) return vec->at(idx);
    return defaultReturn;
  }

  template <typename T>
  void VecTools<T>::cutInterval(
    std::vector<T> &vec,
    std::vector<T> &wasted,
    int begin, int end
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

    // cutting
    std::vector<T> tail = std::vector<T>(vec.begin() + end + 1, vec.end());
    wasted = std::vector<T>(vec.begin() + begin, vec.begin() + end + 1);
    vec = std::vector<T>(vec.begin(), vec.begin() + begin);
    vec.insert(vec.end(), tail.begin(), tail.end());
  }

  template <typename T>
  std::vector<T> VecTools<T>::cutInterval(std::vector<T> &vec, int begin, int end) {
    std::vector<T> wasted;
    VecTools<T>::cutInterval(vec, wasted, begin, end);
    return wasted;
  }

  template <typename T>
  void VecTools<T>::cutSingle(std::vector<T> &vec, T &wasted, int idx) {
    if (vec.size() == 0) return;

    if (idx < 0) idx = 0;
    else if (idx >= vec.size()) idx = vec.size() - 1;

    wasted = vec[idx];
    std::vector<T> tail = std::vector<T>(vec.begin() + idx + 1, vec.end());
    vec = std::vector<T>(vec.begin(), vec.begin() + idx);
    vec.insert(vec.end(), tail.begin(), tail.end());
  }

  template <typename T>
  T VecTools<T>::cutSingle(std::vector<T> &vec, int idx) {
    T wasted = vec[idx];
    VecTools<T>::cutSingle(vec, wasted, idx);
    return wasted;
  }

  template <typename T>
  void VecTools<T>::cutIndexes(
    std::vector<T> &vec,
    std::vector<T> &wasted,
    VEC_INT idxs,
    bool lockedIndex
  ) {
    if (vec.size() == 0) return;
    int last = idxs.size() - 1;

    // ascending
    if (algorithms::Calc::isArithmeticSequence(idxs, 1)) {
      VecTools<T>::cutInterval(vec, wasted, idxs[0], idxs[last]);
    }
    // descending
    else if (algorithms::Calc::isArithmeticSequence(idxs, -1)) {
      VecTools<T>::cutInterval(vec, wasted, idxs[last], idxs[0]);
    }
    // one by one
    else {
      wasted = {};
      bool prevIndex = -1;

      for (int i = 0; i < idxs.size(); i++) {

        if (!lockedIndex || (prevIndex >= 0 && prevIndex != idxs[i])) {
          wasted.push_back(VecTools<T>::cutSingle(vec, idxs[i]));
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
  std::vector<T> VecTools<T>::cutIndexes(
    std::vector<T> &vec,
    VEC_INT idxs,
    bool lockedIndex
  ) {
    std::vector<T> wasted;
    VecTools<T>::cutIndexes(vec, wasted, idxs, lockedIndex);
    return wasted;
  }

  template<>
  VEC_UI VecTools<>::getDifferencesToSize(
    VEC_UI sizes, UI targetSize
  ) {
    UI max = targetSize;

    for (auto &sz : sizes) {
      if (targetSize > 0) {
        if (sz > max && sz <= targetSize) max = sz;
      }
      else if (sz > max) max = sz;
    }

    VEC_UI differences;
    for (auto &sz : sizes) differences.push_back(max - sz);
    
    return differences;
  }

  template <typename T>
  std::vector<T> VecTools<T>::cleanDuplicateInside(
    std::vector<T> &vec,
    std::function<bool(T,T)> equalRule
  ) {
    std::vector<T> wastedVec;
    bool first = false;

    for (int i = 0; i < vec->size(); i++) {
      for (int j = 0; j < vec->size(); j++) {
        bool isEqual = vec->at(i) == vec->at(j);

        if (i != j && (isEqual || equalRule(vec->at(i), vec->at(j)) )) {

          // same address
          if (isEqual && std::is_pointer<T>::value) {
            VecTools<T>::cutSingle(vec, j);
          }
          // same value
          else wastedVec.push_back(VecTools<T>::cutSingle(vec, j));

          j--;
        }
      }
    }

    return wastedVec;
  }

  template <typename T>
  std::vector<T> VecTools<T>::cleanDuplicateToMember(
    std::vector<T> &vec, T mem,
    std::function<bool(T,T)> equalRule
  ) {
    std::vector<T> wastedVec;
    bool first = false;

    for (int i = 0; i < vec->size(); i++) {
      bool isEqual = vec->at(i) == mem;

      if (isEqual || equalRule(vec->at(i), mem)) {

        if (first) {
          // same address
          if (isEqual && std::is_pointer<T>::value) {
            VecTools<T>::cutSingle(vec, i);
          }
          // same value
          else wastedVec.push_back(VecTools<T>::cutSingle(vec, i));
        }
        else first = true;
      }
    }

    return wastedVec;
  }
}}

#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__