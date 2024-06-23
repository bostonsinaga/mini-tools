#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__

namespace mini_tools {
namespace utils {

  template <typename T>
  bool VecTools<T>::isIndexOfVector(std::vector<T> *vec, int idx) {
    if (idx < vec->size() && idx >= 0) return true;
    return false;
  }

  template <typename T>
  T VecTools<T>::getIndexOfVector(std::vector<T> *vec, int idx, T defaultReturn) {
    if (VecTools<T>::isIndexOfVector(vec, idx)) return vec->at(idx);
    return defaultReturn;
  }

  template <typename T>
  T VecTools<T>::cutVector(std::vector<T> *vec, int idx) {
    T wasted = vec->at(idx);
    std::vector<T> tail = std::vector<T>(vec->begin() + idx + 1, vec->end());
    *vec = std::vector<T>(vec->begin(), vec->begin() + idx);
    vec->insert(vec->end(), tail.begin(), tail.end());
    return wasted;
  }

  template <typename T>
  std::vector<T> VecTools<T>::cutVector(std::vector<T> *vec, VEC_INT idxs) {
    std::vector<T> wastedVec;
    for (auto &i : idxs) { wastedVec.push_back(VecTools<T>::cutVector(vec, i)); }
    return wastedVec;
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
    for (auto &sz : sizes) { differences.push_back(max - sz); }
    
    return differences;
  }

  template <typename T>
  std::vector<T> VecTools<T>::cleanDuplicateInsideVector(
    std::vector<T> *vec,
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
            VecTools<T>::cutVector(vec, j);
          }
          // same value
          else wastedVec.push_back(VecTools<T>::cutVector(vec, j));

          j--;
        }
      }
    }

    return wastedVec;
  }

  template <typename T>
  std::vector<T> VecTools<T>::cleanDuplicateToMember(
    std::vector<T> *vec, T mem,
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
            VecTools<T>::cutVector(vec, i);
          }
          // same value
          else wastedVec.push_back(VecTools<T>::cutVector(vec, i));
        }
        else first = true;
      }
    }

    return wastedVec;
  }
}}

#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_CPP__