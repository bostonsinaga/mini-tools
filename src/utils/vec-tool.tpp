#ifndef __MINI_TOOLS__UTILS__VEC_TOOL_TPP__
#define __MINI_TOOLS__UTILS__VEC_TOOL_TPP__

namespace mini_tools {
namespace utils {

  //______________|
  // VECTOR TOOLS |
  //______________|

  template <typename T>
  bool VecTool<T>::hasIndex(CR_SZ targetSz, CR_LLI idx) {
    if (idx < targetSz && idx >= 0) return true;
    return false;
  }

  template <typename T>
  bool VecTool<T>::hasIndex(CR_VEC<T> vec, CR_LLI idx) {
    return VecTool<T>::hasIndex(
      vec.size(), idx
    );
  }

  template <typename T>
  bool VecTool<T>::hasIndices(CR_SZ targetSz, CR_VEC_LLI indices) {
    for (CR_LLI i : indices) {
      if (!hasIndex(targetSz, i)) return false;
    }
    return indices.size() > 0 ? true : false;
  }

  template <typename T>
  bool VecTool<T>::hasIndices(CR_VEC<T> vec, CR_VEC_LLI indices) {
    return VecTool<T>::hasIndices(
      vec.size(), indices
    );
  }

  template <typename T>
  LLI VecTool<T>::getIndex(
    CR_VEC<T> vec,
    CR<T> data,
    EQUAL_RULE equalRule
  ) {
    for (size_t i = 0; i < vec.size(); i++) {
      if (data == vec[i] || equalRule(data, vec[i])) return i;
    }
    return -1;
  }

  template <typename T>
  T VecTool<T>::getAt(
    CR_VEC<T> vec,
    CR_LLI idx,
    CR<T> defaultReturn
  ) {
    if (VecTool<T>::hasIndex(vec, idx)) return vec[idx];
    return defaultReturn;
  }

  /** VECTORS CONNECTORS */

  template <typename T>
  void VecTool<T>::concatCopy(
    VEC<T> &targetVec,
    CR_VEC<T> additionVec
  ) {
    // reserving capacity
    targetVec.reserve(targetVec.size() + additionVec.size());

    // copy the 'additionVec'
    targetVec.insert(targetVec.end(), additionVec.begin(), additionVec.end());
  }

  template <typename T>
  void VecTool<T>::concatCut(
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
  VEC<T> VecTool<T>::joinCopy(
    CR_VEC<T> vecA,
    CR_VEC<T> vecB
  ) {
    VEC<T> newVec;
    VecTool<T>::concatCopy(newVec, vecA);
    VecTool<T>::concatCopy(newVec, vecB);
    return newVec;
  }

  template <typename T>
  VEC<T> VecTool<T>::joinCut(
    VEC<T> &vecA,
    VEC<T> &vecB,
    CR_BOL needShrink
  ) {
    VEC<T> newVec;
    VecTool<T>::concatCut(newVec, vecA, needShrink);
    VecTool<T>::concatCut(newVec, vecB, needShrink);
    return newVec;
  }

  template <typename T>
  VEC<T> VecTool<T>::collapseCopy(CR_VEC2<T> vec) {
    VEC<T> reduction;

    for (CR_VEC<T> mem : vec) {
      VecTool<T>::concatCopy(reduction, mem);
    }

    return reduction;
  }

  template <typename T>
  VEC<T> VecTool<T>::collapseCut(VEC2<T> &vec, CR_BOL needShrink) {
    VEC<T> reduction;

    for (VEC<T> &mem : vec) {
      VecTool<T>::concatCut(reduction, mem, needShrink);
    }

    // release 1D memory
    vec.clear();
    if (needShrink) vec.shrink_to_fit();

    return reduction;
  }

  /** STABLE ERASERS (SLOWER) */

  template <typename T>
  void VecTool<T>::eraseSingleStable(
    VEC<T> &vec,
    CR_SZ index,
    T &extracted
  ) {
    extracted = vec[index];
    vec.erase(vec.begin() + index);
  }

  template <typename T>
  void VecTool<T>::eraseIntervalStable(
    VEC<T> &vec,
    CR_PAIR_SZ interval,
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
  void VecTool<T>::eraseIndicesStable(
    VEC<T> &vec,
    CR_VEC_SZ indices,
    VEC<T> &extracted
  ) {
    for (CR_SZ i : indices) {
      extracted.push_back(vec[i]);
      vec.erase(vec.begin() + i);
    }
  }

  template <typename T>
  void VecTool<T>::eraseSingleStable(
    VEC<T> &vec,
    CR_SZ index
  ) {
    vec.erase(vec.begin() + index);
  }

  template <typename T>
  void VecTool<T>::eraseIntervalStable(
    VEC<T> &vec,
    CR_PAIR_SZ interval
  ) {
    vec.erase(
      vec.begin() + interval.first,
      vec.begin() + interval.second + 1
    );
  }

  template <typename T>
  void VecTool<T>::eraseIndicesStable(
    VEC<T> &vec,
    CR_VEC_SZ indices
  ) {
    for (CR_SZ i : indices) {
      vec.erase(vec.begin() + i);
    }
  }

  /** UNSTABLE ERASERS (FASTER) */

  template <typename T>
  void VecTool<T>::eraseSingleUnstable(
    VEC<T> &vec,
    CR_SZ index,
    T &extracted
  ) {
    extracted = vec[index];
    vec[index] = vec.back();
    vec.pop_back();
  }

  template <typename T>
  void VecTool<T>::eraseIntervalUnstable(
    VEC<T> &vec,
    CR_PAIR_SZ interval,
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
  void VecTool<T>::eraseIndicesUnstable(
    VEC<T> &vec,
    CR_VEC_SZ indices,
    VEC<T> &extracted
  ) {
    for (CR_SZ i : indices) {
      extracted.push_back(vec[i]);
      vec[i] = vec.back();
      vec.pop_back();
    }
  }

  template <typename T>
  void VecTool<T>::eraseSingleUnstable(
    VEC<T> &vec,
    CR_SZ index
  ) {
    vec[index] = vec.back();
    vec.pop_back();
  }

  template <typename T>
  void VecTool<T>::eraseIntervalUnstable(
    VEC<T> &vec,
    CR_PAIR_SZ interval
  ) {
    for (size_t i = interval.first; i <= interval.second; i++) {
      vec[i] = vec.back();
      vec.pop_back();
    }
  }

  template <typename T>
  void VecTool<T>::eraseIndicesUnstable(
    VEC<T> &vec,
    CR_VEC_SZ indices
  ) {
    for (CR_SZ i : indices) {
      vec[i] = vec.back();
      vec.pop_back();
    }
  }

  /** STABLE EXTRACTORS */

  template <typename T>
  T VecTool<T>::extractSingleStable(
    VEC<T> &vec,
    CR_SZ index
  ) {
    T extracted;
    VecTool<T>::eraseSingleStable(vec, index, extracted);
    return extracted;
  }

  template <typename T>
  VEC<T> VecTool<T>::extractIntervalStable(
    VEC<T> &vec,
    CR_PAIR_SZ interval
  ) {
    VEC<T> extracted;
    VecTool<T>::eraseIntervalStable(vec, interval, extracted);
    return extracted;
  }

  template <typename T>
  VEC<T> VecTool<T>::extractIndicesStable(
    VEC<T> &vec,
    CR_VEC_SZ indices
  ) {
    VEC<T> extracted;
    VecTool<T>::eraseIndicesStable(vec, indices, extracted);
    return extracted;
  }

  /** UNSTABLE EXTRACTORS */

  template <typename T>
  T VecTool<T>::extractSingleUnstable(
    VEC<T> &vec,
    CR_SZ index
  ) {
    T extracted;
    VecTool<T>::eraseSingleUnstable(vec, index, extracted);
    return extracted;
  }

  template <typename T>
  VEC<T> VecTool<T>::extractIntervalUnstable(
    VEC<T> &vec,
    CR_PAIR_SZ interval
  ) {
    VEC<T> extracted;
    VecTool<T>::eraseIntervalUnstable(vec, interval, extracted);
    return extracted;
  }

  template <typename T>
  VEC<T> VecTool<T>::extractIndicesUnstable(
    VEC<T> &vec,
    CR_VEC_SZ indices
  ) {
    VEC<T> extracted;
    VecTool<T>::eraseIndicesUnstable(vec, indices, extracted);
    return extracted;
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
      if (!VecTool<T>::hasIndex(targetSz, indices[i])) {

        if (needRemove) {
          VecTool<T>::extractSingleStable(indices, i);
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
  void VecTool<T>::fixIndices(
    VEC<T> &vec,
    VEC_LLI &indices,
    CR_BOL needRemove
  ) {
    VecTool<T>::fixIndices(
      vec.size(), indices, needRemove
    );
  }

  template <typename T>
  VEC_LLI VecTool<T>::fixIndices(
    CR_SZ targetSz,
    CR_VEC_LLI indices,
    CR_BOL needRemove
  ) {
    VEC_LLI newIndices = indices;

    VecTool<T>::fixIndices(
      targetSz, newIndices, needRemove
    );

    return newIndices;
  }

  template <typename T>
  VEC_LLI VecTool<T>::fixIndices(
    VEC<T> &vec,
    CR_VEC_LLI indices,
    CR_BOL needRemove
  ) {
    return VecTool<T>::fixIndices(
      vec.size(), indices, needRemove
    );
  }

  template <typename T>
  void VecTool<T>::fixIndexInterval(
    CR_SZ targetSz, LLI &begin, LLI &end
  ) {
    if (begin > end) std::swap(begin, end);
    if (begin < 0 || begin > targetSz) begin = 0;
    if (end <= 0 || end >= targetSz) end = targetSz - 1;
  }

  template <typename T>
  void VecTool<T>::fixIndexInterval(
    CR_SZ targetSz, PAIR_LLI &interval
  ) {
    VecTool<T>::fixIndexInterval(
      targetSz, interval.first, interval.second
    );
  }

  template <typename T>
  void VecTool<T>::fixIndexInterval(
    VEC<T> &vec, LLI &begin, LLI &end
  ) {
    VecTool<T>::fixIndexInterval(
      vec.size(), begin, end
    );
  }

  template <typename T>
  void VecTool<T>::fixIndexInterval(
    VEC<T> &vec, PAIR_LLI &interval
  ) {
    VecTool<T>::fixIndexInterval(
      vec.size(), interval.first, interval.second
    );
  }

  template <typename T>
  PAIR_LLI VecTool<T>::fixIndexInterval(
    CR_SZ targetSz, CR_LLI begin, CR_LLI end
  ) {
    PAIR_LLI newInterval {begin, end};

    VecTool<T>::fixIndexInterval(
      targetSz, newInterval.first, newInterval.second
    );

    return newInterval;
  }

  template <typename T>
  PAIR_LLI VecTool<T>::fixIndexInterval(
    CR_SZ targetSz, CR_PAIR_LLI interval
  ) {
    return VecTool<T>::fixIndexInterval(
      targetSz, interval.first, interval.second
    );
  }

  template <typename T>
  PAIR_LLI VecTool<T>::fixIndexInterval(
    VEC<T> &vec, CR_LLI begin, CR_LLI end
  ) {
    return VecTool<T>::fixIndexInterval(
      vec.size(), begin, end
    );
  }

  template <typename T>
  PAIR_LLI VecTool<T>::fixIndexInterval(
    VEC<T> &vec, CR_PAIR_LLI interval
  ) {
    return VecTool<T>::fixIndexInterval(
      vec.size(), interval.first, interval.second
    );
  }

  template <typename T>
  bool VecTool<T>::isIndexIntervalValid(
    CR_SZ targetSz, CR_LLI begin, CR_LLI end
  ) {
    if (begin < end &&
      begin >= 0 && begin < targetSz - 1 &&
      end > 0 && end < targetSz
    ) { return true; }
    return false;
  }

  template <typename T>
  bool VecTool<T>::isIndexIntervalValid(
    CR_SZ targetSz, CR_PAIR_LLI interval
  ) {
    return VecTool<T>::isIndexIntervalValid(
      targetSz, interval.first, interval.second
    );
  }

  template <typename T>
  bool VecTool<T>::isIndexIntervalValid(
    VEC<T> &vec, CR_LLI begin, CR_LLI end
  ) {
    return VecTool<T>::isIndexIntervalValid(
      vec.size(), begin, end
    );
  }

  template <typename T>
  bool VecTool<T>::isIndexIntervalValid(
    VEC<T> &vec, CR_PAIR_LLI interval
  ) {
    return VecTool<T>::isIndexIntervalValid(
      vec.size(), interval.first, interval.second
    );
  }

  //____________|
  // SIZE TOOLS |
  //____________|

  template <typename T>
  VEC_SZ VecTool<T>::generateSizes(CR_VEC2<T> vecs) {
    VEC_SZ sizes;

    for (CR_VEC<T> v : vecs) {
      sizes.push_back(v.size());
    }

    return sizes;
  }

  template <typename T>
  size_t VecTool<T>::getMin(VEC_SZ &sizes) {
    size_t min = 0;

    for (CR_LLI sz : sizes) {
      if (sz < min) min = sz;
    }

    return min;
  }

  template <typename T>
  size_t VecTool<T>::getMax(VEC_SZ &sizes) {
    size_t max = 0;

    for (CR_SZ sz : sizes) {
      if (sz > max) max = sz;
    }

    return max;
  }

  template <typename T>
  size_t VecTool<T>::getMin(CR_VEC2<T> vecs) {
    VEC_SZ sizes = VecTool<T>::generateSizes(vecs);
    return VecTool<T>::getMin(sizes);
  }

  template <typename T>
  size_t VecTool<T>::getMax(CR_VEC2<T> vecs) {
    VEC_SZ sizes = VecTool<T>::generateSizes(vecs);
    return VecTool<T>::getMax(sizes);
  }

  template <typename T>
  VEC_SZ VecTool<T>::getDifferences(VEC_SZ &sizes) {

    VEC_SZ differences;
    size_t max = VecTool<T>::getMax(sizes);

    for (CR_SZ sz : sizes) {
      differences.push_back(max - sz);
    }

    return differences;
  }

  template <typename T>
  VEC_LLI VecTool<T>::getDifferences(
    VEC_LLI &sizes, CR_LLI targetSz
  ) {
    VEC_LLI differences;

    for (CR_LLI sz : sizes) {
      differences.push_back(targetSz - sz);
    }

    return differences;
  }

  template <typename T>
  VEC_SZ VecTool<T>::getDifferences(CR_VEC2<T> vecs) {
    VEC_SZ sizes = VecTool<T>::generateSizes(vecs);
    return VecTool<T>::getDifferences(sizes);
  }

  template <typename T>
  VEC_LLI VecTool<T>::getDifferences(
    CR_VEC2<T> vecs,
    CR_LLI targetSz
  ) {
    VEC_LLI sizes = VecTool<T>::generateSizes(vecs);
    return VecTool<T>::getDifferences(sizes, targetSz);
  }

  template <typename T>
  void VecTool<T>::balance(
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
  void VecTool<T>::balance(
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
  void VecTool<T>::balance(
    VEC2<T> &vecs,
    CR<T> padding
  ) {
    VecTool<T>::balance(
      VecTool<T>::getDifferences(vecs),
      vecs, padding
    );
  }

  template <typename T>
  void VecTool<T>::balance(
    VEC2<T> &vecs,
    CR<T> padding,
    LLI targetSz
  ) {
    if (targetSz < 0) targetSz = 0;

    VecTool<T>::balance(
      VecTool<T>::getDifferences(vecs, targetSz),
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
    VecTool<T>::EQUAL_RULE &equalRule,
    CR<T> &a,
    CR<T> &b,
    CR_SZ cutIdx
  ) {
    if (a == b || equalRule(a, b)) {

      if constexpr (U == VECDUP_STABLE) {
        wasted.push_back(
          VecTool<T>::extractSingleStable(vec, cutIdx)
        );
      }
      else wasted.push_back(
        VecTool<T>::extractSingleUnstable(vec, cutIdx)
      );

      return true;
    }

    return false;
  }

  template <typename T, VECDUP_ENUM U>
  VEC<T> VecDupTools<T, U>::eliminate(
    VEC<T> &vec,
    CR_BOL originalAscending,
    VecTool<T>::EQUAL_RULE equalRule
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

    return wasted;
  }

  template <typename T, VECDUP_ENUM U>
  VEC<T> VecDupTools<T, U>::clean(
    VEC<T> &vec,
    CR<T> val,
    CR_BOL originalAscending,
    VecTool<T>::EQUAL_RULE equalRule
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

    return wasted;
  }
}}

#endif // __MINI_TOOLS__UTILS__VEC_TOOL_TPP__