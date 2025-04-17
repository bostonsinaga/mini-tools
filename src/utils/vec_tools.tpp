#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_TPP__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_TPP__

namespace mini_tools {
namespace utils {

  //______________|
  // VECTOR TOOLS |
  //______________|

  template <typename T>
  bool VecTools<T>::hasIndex(CR_SZ targetSz, CR_LLI idx) {
    if (idx < targetSz && idx >= 0) return true;
    return false;
  }

  template <typename T>
  bool VecTools<T>::hasIndex(VEC<T> &vec, CR_LLI idx) {
    if (idx < vec.size() && idx >= 0) return true;
    return false;
  }

  template <typename T>
  bool VecTools<T>::hasIndices(CR_SZ targetSz, CR_VEC_LLI indices) {
    for (CR_LLI i : indices) {
      if (!hasIndex(targetSz, i)) return false;
    }
    return indices.size() > 0 ? true : false;
  }

  template <typename T>
  bool VecTools<T>::hasIndices(VEC<T> &vec, CR_VEC_LLI indices) {
    for (CR_LLI i : indices) {
      if (!hasIndex(vec, i)) return false;
    }
    return indices.size() > 0 ? true : false;
  }

  template <typename T>
  LLI VecTools<T>::getIndex(
    VEC<T> &vec,
    CR<T> data,
    EQUAL_RULE equalRule
  ) {
    for (size_t i = 0; i < vec.size(); i++) {
      if (data == vec[i] || equalRule(data, vec[i])) return i;
    }
    return -1;
  }

  template <typename T>
  T VecTools<T>::getAt(VEC<T> &vec, CR_LLI idx, CR<T> defaultReturn) {
    if (VecTools<T>::hasIndex(vec, idx)) return vec[idx];
    return defaultReturn;
  }

  /** VECTORS CONNECTORS */

  template <typename T>
  void VecTools<T>::concatCopy(
    VEC<T> &targetVec,
    CR_VEC<T> additionVec
  ) {
    // reserving capacity
    targetVec.reserve(targetVec.size() + additionVec.size());

    // copy the 'additionVec'
    targetVec.insert(targetVec.end(), additionVec.begin(), additionVec.end());
  }

  template <typename T>
  void VecTools<T>::concatCut(
    VEC<T> &targetVec,
    VEC<T> &additionVec,
    CR_BOL needShrink
  ) {
    // reserving capacity
    targetVec.reserve(targetVec.size() + additionVec.size());

    // cut the 'additionVec'
    targetVec.insert(
      targetVec.end(),
      std::make_move_iterator(additionVec.begin()),
      std::make_move_iterator(additionVec.end())
    );

    // release 2D memory
    additionVec.clear();
    if (needShrink) additionVec.shrink_to_fit();
  }

  template <typename T>
  VEC<T> VecTools<T>::joinCopy(
    CR_VEC<T> vecA,
    CR_VEC<T> vecB
  ) {
    VEC<T> newVec;
    VecTools<T>::concatCopy(newVec, vecA);
    VecTools<T>::concatCopy(newVec, vecB);
    return newVec;
  }

  template <typename T>
  VEC<T> VecTools<T>::joinCut(
    VEC<T> &vecA,
    VEC<T> &vecB,
    CR_BOL needShrink
  ) {
    VEC<T> newVec;
    VecTools<T>::concatCut(newVec, vecA, needShrink);
    VecTools<T>::concatCut(newVec, vecB, needShrink);
    return newVec;
  }

  template <typename T>
  VEC<T> VecTools<T>::collapseCopy(CR_VEC2<T> vec) {
    VEC<T> reduction;

    for (CR_VEC<T> mem : vec) {
      VecTools<T>::concatCopy(reduction, mem);
    }

    return std::move(reduction);
  }

  template <typename T>
  VEC<T> VecTools<T>::collapseCut(VEC2<T> &vec, CR_BOL needShrink) {
    VEC<T> reduction;

    for (VEC<T> &mem : vec) {
      VecTools<T>::concatCut(reduction, mem, needShrink);
    }

    // release 1D memory
    vec.clear();
    if (needShrink) vec.shrink_to_fit();

    return std::move(reduction);
  }

  /** STABLE ERASERS (SLOWER) */

  template <typename T>
  void VecTools<T>::eraseSingleStable(
    VEC<T> &vec,
    CR_SZ index,
    T extracted
  ) {
    extracted = vec[index];
    vec.erase(vec.begin() + index);
  }

  template <typename T>
  void VecTools<T>::eraseIntervalStable(
    VEC<T> &vec,
    CR_PAIR<size_t> interval,
    VEC<T> &extracted
  ) {
    extracted = VEC<T>(
      vec.begin() + interval.first,
      vec.begin() + interval.second + 1
    );

    vec.erase(
      vec.begin() + interval.first,
      vec.begin() + interval.second + 1
    );
  }

  template <typename T>
  void VecTools<T>::eraseIndicesStable(
    VEC<T> &vec,
    CR_VEC<size_t> indices,
    VEC<T> &extracted
  ) {
    for (CR_SZ i : indices) {
      extracted.push_back(vec[i]);
      vec.erase(vec.begin() + i);
    }
  }

  /** UNSTABLE ERASERS (FASTER) */

  template <typename T>
  void VecTools<T>::eraseSingleUnstable(
    VEC<T> &vec,
    CR_SZ index,
    T &extracted
  ) {
    extracted = vec[index];
    vec[index] = vec.back();
    vec.pop_back();
  }

  template <typename T>
  void VecTools<T>::eraseIntervalUnstable(
    VEC<T> &vec,
    CR_PAIR<size_t> interval,
    VEC<T> &extracted
  ) {
    extracted = VEC<T>(
      vec.begin() + interval.first,
      vec.begin() + interval.second + 1
    );

    for (size_t i = interval.first; i <= interval.second; i++) {
      vec[i] = vec.back();
      vec.pop_back();
    }
  }

  template <typename T>
  void VecTools<T>::eraseIndicesUnstable(
    VEC<T> &vec,
    CR_VEC<size_t> indices,
    VEC<T> &extracted
  ) {
    for (CR_SZ i : indices) {
      extracted.push_back(vec[i]);
      vec[i] = vec.back();
      vec.pop_back();
    }
  }

  /** STABLE EXTRACTORS */

  template <typename T>
  T VecTools<T>::extractSingleStable(
    VEC<T> &vec,
    CR_SZ index
  ) {
    T extracted;
    VecTools<T>::eraseSingleStable(vec, index, extracted);
    return std::move(extracted);
  }

  template <typename T>
  VEC<T> VecTools<T>::extractIntervalStable(
    VEC<T> &vec,
    CR_PAIR<size_t> interval
  ) {
    VEC<T> extracted;
    VecTools<T>::eraseIntervalStable(vec, interval, extracted);
    return std::move(extracted);
  }

  template <typename T>
  VEC<T> VecTools<T>::extractIndicesStable(
    VEC<T> &vec,
    CR_VEC<size_t> indices
  ) {
    VEC<T> extracted;
    VecTools<T>::eraseIndicesStable(vec, indices, extracted);
    return std::move(extracted);
  }

  /** UNSTABLE EXTRACTORS */

  template <typename T>
  T VecTools<T>::extractSingleUnstable(
    VEC<T> &vec,
    CR_SZ index
  ) {
    T extracted;
    VecTools<T>::eraseSingleUnstable(vec, index, extracted);
    return std::move(extracted);
  }

  template <typename T>
  VEC<T> VecTools<T>::extractIntervalUnstable(
    VEC<T> &vec,
    CR_PAIR<size_t> interval
  ) {
    VEC<T> extracted;
    VecTools<T>::eraseIntervalUnstable(vec, interval, extracted);
    return std::move(extracted);
  }

  template <typename T>
  VEC<T> VecTools<T>::extractIndicesUnstable(
    VEC<T> &vec,
    CR_VEC<size_t> indices
  ) {
    VEC<T> extracted;
    VecTools<T>::eraseIndicesUnstable(vec, indices, extracted);
    return std::move(extracted);
  }

  /** INDEX LIMITERS */

  template <typename T>
  static void fixIndices(
    CR_SZ targetSz,
    VEC_LLI &indices,
    CR_BOL needRemove
  ) {
    if (!targetSz) return;

    for (LLI i = 0; i < indices.size(); i++) {
      if (!VecTools<T>::hasIndex(targetSz, indices[i])) {

        if (needRemove) {
          VecTools<T>::extractSingleStable(indices, i);
          i--;
        }
        else {
          if (indices[i] < 0) indices[i] = 0;
          else if (indices[i] >= targetSz) indices[i] = targetSz - 1;
        }
      }
    }
  }

  template <typename T>
  void VecTools<T>::fixIndices(
    VEC<T> &vec,
    VEC_LLI &indices,
    CR_BOL needRemove
  ) {
    VecTools<T>::fixIndices(
      vec.size(), indices, needRemove
    );
  }

  template <typename T>
  VEC_LLI VecTools<T>::fixIndices(
    CR_SZ targetSz,
    CR_VEC_LLI indices,
    CR_BOL needRemove
  ) {
    VEC_LLI newIndices = indices;

    VecTools<T>::fixIndices(
      targetSz, newIndices, needRemove
    );

    return newIndices;
  }

  template <typename T>
  VEC_LLI VecTools<T>::fixIndices(
    VEC<T> &vec,
    CR_VEC_LLI indices,
    CR_BOL needRemove
  ) {
    return VecTools<T>::fixIndices(
      vec.size(), indices, needRemove
    );
  }

  template <typename T>
  void VecTools<T>::fixIndexInterval(
    CR_SZ targetSz, LLI &begin, LLI &end
  ) {
    if (begin > end) std::swap(begin, end);
    if (begin < 0 || begin > targetSz) begin = 0;
    if (end <= 0 || end >= targetSz) end = targetSz - 1;
  }

  template <typename T>
  void VecTools<T>::fixIndexInterval(
    CR_SZ targetSz, PAIR<LLI> &interval
  ) {
    VecTools<T>::fixIndexInterval(
      targetSz, interval.first, interval.second
    );
  }

  template <typename T>
  void VecTools<T>::fixIndexInterval(
    VEC<T> &vec, LLI &begin, LLI &end
  ) {
    VecTools<T>::fixIndexInterval(
      vec.size(), begin, end
    );
  }

  template <typename T>
  void VecTools<T>::fixIndexInterval(
    VEC<T> &vec, PAIR<LLI> &interval
  ) {
    VecTools<T>::fixIndexInterval(
      vec.size(), interval.first, interval.second
    );
  }

  template <typename T>
  PAIR<LLI> VecTools<T>::fixIndexInterval(
    CR_SZ targetSz, CR_LLI begin, CR_LLI end
  ) {
    PAIR<LLI> newInterval {begin, end};

    VecTools<T>::fixIndexInterval(
      targetSz, newInterval.first, newInterval.second
    );

    return std::move(newInterval);
  }

  template <typename T>
  PAIR<LLI> VecTools<T>::fixIndexInterval(
    CR_SZ targetSz, CR_PAIR<LLI> interval
  ) {
    return fixIndexInterval(
      targetSz, interval.first, interval.second
    );
  }

  template <typename T>
  PAIR<LLI> VecTools<T>::fixIndexInterval(
    VEC<T> &vec, CR_LLI begin, CR_LLI end
  ) {
    return fixIndexInterval(
      vec.size(), begin, end
    );
  }

  template <typename T>
  PAIR<LLI> VecTools<T>::fixIndexInterval(
    VEC<T> &vec, CR_PAIR<LLI> interval
  ) {
    return fixIndexInterval(
      vec.size(), interval.first, interval.second
    );
  }

  template <typename T>
  bool VecTools<T>::isIndexIntervalValid(
    CR_SZ targetSz, CR_LLI begin, CR_LLI end
  ) {
    if (begin < end &&
      begin >= 0 && begin < targetSz - 1 &&
      end > 0 && end < targetSz
    ) { return true; }
    return false;
  }

  template <typename T>
  bool VecTools<T>::isIndexIntervalValid(
    CR_SZ targetSz, CR_PAIR<LLI> interval
  ) {
    return isIndexIntervalValid(
      targetSz, interval.first, interval.second
    );
  }

  template <typename T>
  bool VecTools<T>::isIndexIntervalValid(
    VEC<T> &vec, CR_LLI begin, CR_LLI end
  ) {
    return isIndexIntervalValid(
      vec.size(), begin, end
    );
  }

  template <typename T>
  bool VecTools<T>::isIndexIntervalValid(
    VEC<T> &vec, CR_PAIR<LLI> interval
  ) {
    return isIndexIntervalValid(
      vec.size(), interval.first, interval.second
    );
  }

  //____________|
  // SIZE TOOLS |
  //____________|

  template <typename T>
  VEC_SZ VecTools<T>::generateSizes(CR_VEC2<T> vecs) {
    VEC_SZ sizes;

    for (CR_VEC<T> v : vecs) {
      sizes.push_back(v.size());
    }

    return std::move(sizes);
  }

  template <typename T>
  size_t VecTools<T>::getMin(VEC_SZ &sizes) {
    size_t min = 0;

    for (CR_LLI sz : sizes) {
      if (sz < min) min = sz;
    }

    return min;
  }

  template <typename T>
  size_t VecTools<T>::getMax(VEC_SZ &sizes) {
    size_t max = 0;

    for (CR_SZ sz : sizes) {
      if (sz > max) max = sz;
    }

    return max;
  }

  template <typename T>
  size_t VecTools<T>::getMin(CR_VEC2<T> vecs) {
    VEC_SZ sizes = VecTools<T>::generateSizes(vecs);
    return VecTools<T>::getMin(sizes);
  }

  template <typename T>
  size_t VecTools<T>::getMax(CR_VEC2<T> vecs) {
    VEC_SZ sizes = VecTools<T>::generateSizes(vecs);
    return VecTools<T>::getMax(sizes);
  }

  template <typename T>
  VEC_SZ VecTools<T>::getDifferences(VEC_SZ &sizes) {

    VEC_SZ differences;
    size_t max = VecTools<T>::getMax(sizes);

    for (CR_SZ sz : sizes) {
      differences.push_back(max - sz);
    }

    return std::move(differences);
  }

  template <typename T>
  VEC_LLI VecTools<T>::getDifferences(
    VEC_LLI &sizes, CR_LLI targetSz
  ) {
    VEC_LLI differences;

    for (CR_LLI sz : sizes) {
      differences.push_back(targetSz - sz);
    }

    return std::move(differences);
  }

  template <typename T>
  VEC_SZ VecTools<T>::getDifferences(CR_VEC2<T> vecs) {
    VEC_SZ sizes = VecTools<T>::generateSizes(vecs);
    return std::move(VecTools<T>::getDifferences(sizes));
  }

  template <typename T>
  VEC_LLI VecTools<T>::getDifferences(
    CR_VEC2<T> vecs,
    CR_LLI targetSz
  ) {
    VEC_LLI sizes = VecTools<T>::generateSizes(vecs);
    return std::move(VecTools<T>::getDifferences(sizes, targetSz));
  }

  template <typename T>
  void VecTools<T>::balance(
    CR_VEC_SZ differences,
    VEC2<T> &vecs,
    CR<T> padding
  ) {
    for (size_t i = 0; i < vecs.size(); i++) {
      std::vector<T> additions(differences[i], padding);
      vecs[i].reserve(vecs[i].size() + differences[i]);
      vecs[i].insert(vecs[i].end(), additions.begin(), additions.end());
    }
  }

  template <typename T>
  void VecTools<T>::balance(
    CR_VEC_LLI differences,
    VEC2<T> &vecs,
    CR<T> padding
  ) {
    for (size_t i = 0; i < vecs.size(); i++) {
      if (differences[i] < 0) {
        vecs[i] = std::vector<T>(
          vecs[i].begin(),
          vecs[i].end() + differences[i]
        );
      }
      else if (differences[i] > 0) {
        std::vector<T> additions(differences[i], padding);
        vecs[i].reserve(vecs[i].size() + differences[i]);
        vecs[i].insert(vecs[i].end(), additions.begin(), additions.end());
      }
    }
  }

  template <typename T>
  void VecTools<T>::balance(
    VEC2<T> &vecs,
    CR<T> padding
  ) {
    VecTools<T>::balance(
      VecTools<T>::getDifferences(vecs),
      vecs, padding
    );
  }

  template <typename T>
  void VecTools<T>::balance(
    VEC2<T> &vecs,
    CR<T> padding,
    LLI targetSz
  ) {
    if (targetSz < 0) targetSz = 0;

    VecTools<T>::balance(
      VecTools<T>::getDifferences(vecs, targetSz),
      vecs, padding
    );
  }

  //__________________________|
  // VECTOR DUPLICATION TOOLS |
  //__________________________|

  template <typename T, VECDUP_ENUM U>
  bool VecDupTools<T, U>::fillWasted(
    VEC<T> &vec,
    VEC<T> &wasted,
    VecTools<T>::EQUAL_RULE &equalRule,
    CR<T> &a,
    CR<T> &b,
    CR_SZ cutIdx
  ) {
    if (a == b || equalRule(a, b)) {

      if constexpr (U == VECDUP_STABLE) {
        wasted.push_back(
          VecTools<T>::extractSingleStable(vec, cutIdx)
        );
      }
      else wasted.push_back(
        VecTools<T>::extractSingleUnstable(vec, cutIdx)
      );

      return true;
    }

    return false;
  }

  template <typename T, VECDUP_ENUM U>
  VEC<T> VecDupTools<T, U>::eliminate(
    VEC<T> &vec,
    CR_BOL originalAscending,
    VecTools<T>::EQUAL_RULE equalRule
  ) {
    VEC<T> wasted;

    if (originalAscending) {

      for (LLI i = 0; i < vec.size() - 1; i++) {
        for (LLI j = i+1; j < vec.size(); j++) {

          if (VecDupTools<T, U>::fillWasted(
            vec, wasted, equalRule,
            vec[i], vec[j], j
          )) { j--; }
        }
      }
    }
    else for (LLI i = vec.size() - 1; i > 0; i--) {
      for (LLI j = i - 1; j >= 0; j--) {

        if (VecDupTools<T, U>::fillWasted(
          vec, wasted, equalRule,
          vec[i], vec[j], j
        )) { i--; }
      }
    }

    return std::move(wasted);
  }

  template <typename T, VECDUP_ENUM U>
  VEC<T> VecDupTools<T, U>::clean(
    VEC<T> &vec,
    CR<T> val,
    CR_BOL originalAscending,
    VecTools<T>::EQUAL_RULE equalRule
  ) {
    VEC<T> wasted;

    if (originalAscending) {
      for (LLI i = 0; i < vec.size(); i++) {

        if (VecDupTools<T, U>::fillWasted(
          vec, wasted, equalRule,
          val, vec[i], i
        )) { i--; }
      }
    }
    else for (size_t i = vec.size() - 1; i >= 0; i--) {
      VecDupTools<T, U>::fillWasted(
        vec, wasted, equalRule,
        val, vec[i], i
      );
    }

    return std::move(wasted);
  }
}}

#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_TPP__