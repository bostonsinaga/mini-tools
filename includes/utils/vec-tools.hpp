#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_HPP__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_HPP__

#include "types.hpp"

namespace mini_tools {
namespace utils {

  //______________|
  // VECTOR TOOLS |
  //______________|

  template <class T>
  class VecTools final {
  public:
    VecTools() = delete;
    typedef std::function<bool(CR<T>,CR<T>)> EQUAL_RULE;

    static bool hasIndex(CR_SZ targetSz, CR_LLI idx);
    static bool hasIndex(CR_VEC<T> vec, CR_LLI idx);
    static bool hasIndices(CR_SZ targetSz, CR_VEC_LLI indices);
    static bool hasIndices(CR_VEC<T> vec, CR_VEC_LLI indices);

    // return -1 if not found
    static LLI getIndex(
      CR_VEC<T> vec,
      CR<T> data,
      // repeated and compared 'T' parameters
      EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );

    static T getAt(
      CR_VEC<T> vec,
      CR_LLI idx,
      CR<T> defaultReturn
    );

    /**
     * VECTORS CONNECTORS
     * Connect vector to vector.
     */

    static void concatCopy(
      VEC<T> &targetVec,
      CR_VEC<T> additionVec
    );

    static void concatCut(
      VEC<T> &targetVec,
      VEC<T> &additionVec,
      CR_BOL needShrink = true
    );

    /** Connect 2 vectors to a vector */

    static VEC<T> joinCopy(
      CR_VEC<T> vecA,
      CR_VEC<T> vecB
    );

    static VEC<T> joinCut(
      VEC<T> &vecA,
      VEC<T> &vecB,
      CR_BOL needShrink = true
    );

    // 'T' can also be a vector for multidimensional
    static VEC<T> collapseCopy(CR_VEC2<T> vec);
    static VEC<T> collapseCut(VEC2<T> &vec, CR_BOL needShrink = true);

    /**
     * NOTE:
     * Make sure the indices match the size of 'vec' parameter
     * or use 'fixIndices' and 'fixIndexInterval' methods
     * before calling 'erase..' or 'extract..' to prevent
     * undefined behavior when these methods accessing the vector.
     */

    /** STABLE ERASERS (SLOWER) */

    static void eraseSingleStable(
      VEC<T> &vec,
      CR_SZ index,
      T &extracted
    );

    static void eraseIntervalStable(
      VEC<T> &vec,
      CR_PAIR_SZ interval,
      VEC<T> &extracted
    );

    static void eraseIndicesStable(
      VEC<T> &vec,
      CR_VEC_SZ indices,
      VEC<T> &extracted
    );

    static void eraseSingleStable(
      VEC<T> &vec,
      CR_SZ index
    );

    static void eraseIntervalStable(
      VEC<T> &vec,
      CR_PAIR_SZ interval
    );

    static void eraseIndicesStable(
      VEC<T> &vec,
      CR_VEC_SZ indices
    );

    /** UNSTABLE ERASERS (FASTER) */

    static void eraseSingleUnstable(
      VEC<T> &vec,
      CR_SZ index,
      T &extracted
    );

    static void eraseIntervalUnstable(
      VEC<T> &vec,
      CR_PAIR_SZ interval,
      VEC<T> &extracted
    );

    static void eraseIndicesUnstable(
      VEC<T> &vec,
      CR_VEC_SZ indices,
      VEC<T> &extracted
    );

    static void eraseSingleUnstable(
      VEC<T> &vec,
      CR_SZ index
    );

    static void eraseIntervalUnstable(
      VEC<T> &vec,
      CR_PAIR_SZ inter
    );

    static void eraseIndicesUnstable(
      VEC<T> &vec,
      CR_VEC_SZ indice
    );

    /** STABLE EXTRACTORS */

    static T extractSingleStable(
      VEC<T> &vec,
      CR_SZ index
    );

    static VEC<T> extractIntervalStable(
      VEC<T> &vec,
      CR_PAIR_SZ interval
    );

    static VEC<T> extractIndicesStable(
      VEC<T> &vec,
      CR_VEC_SZ indices
    );

    /** UNSTABLE EXTRACTORS */

    static T extractSingleUnstable(
      VEC<T> &vec,
      CR_SZ index
    );

    static VEC<T> extractIntervalUnstable(
      VEC<T> &vec,
      CR_PAIR_SZ interval
    );

    static VEC<T> extractIndicesUnstable(
      VEC<T> &vec,
      CR_VEC_SZ indices
    );

    /** INDEX LIMITERS */

    static void fixIndices(
      CR_SZ targetSz,
      VEC_LLI &indices,
      CR_BOL needRemove = true
    );

    static void fixIndices(
      VEC<T> &vec,
      VEC_LLI &indices,
      CR_BOL needRemove = true
    );

    static VEC_LLI fixIndices(
      CR_SZ targetSz,
      CR_VEC_LLI indices,
      CR_BOL needRemove = true
    );

    static VEC_LLI fixIndices(
      VEC<T> &vec,
      CR_VEC_LLI indices,
      CR_BOL needRemove = true
    );

    /** Keep range of values between 0 to size - 1 */

    static void fixIndexInterval(CR_SZ targetSz, LLI &begin, LLI &end);
    static void fixIndexInterval(CR_SZ targetSz, PAIR_LLI &interval);
    static void fixIndexInterval(VEC<T> &vec, LLI &begin, LLI &end);
    static void fixIndexInterval(VEC<T> &vec, PAIR_LLI &interval);

    static PAIR_LLI fixIndexInterval(CR_SZ targetSz, CR_LLI begin, CR_LLI end);
    static PAIR_LLI fixIndexInterval(CR_SZ targetSz, CR_PAIR_LLI interval);
    static PAIR_LLI fixIndexInterval(VEC<T> &vec, CR_LLI begin, CR_LLI end);
    static PAIR_LLI fixIndexInterval(VEC<T> &vec, CR_PAIR_LLI interval);

    // check range of values between 0 to size - 1
    static bool isIndexIntervalValid(CR_SZ targetSz, CR_LLI begin, CR_LLI end);
    static bool isIndexIntervalValid(CR_SZ targetSz, CR_PAIR_LLI interval);
    static bool isIndexIntervalValid(VEC<T> &vec, CR_LLI begin, CR_LLI end);
    static bool isIndexIntervalValid(VEC<T> &vec, CR_PAIR_LLI interval);

    //____________|
    // SIZE TOOLS |
    //____________|

  private:
    static size_t getMin(VEC_SZ &sizes);
    static size_t getMax(VEC_SZ &sizes);
    static VEC_SZ getDifferences(VEC_SZ &sizes);
    static VEC_LLI getDifferences(VEC_LLI &sizes, CR_LLI targetSz);
    static void balance(CR_VEC_SZ differences, VEC2<T> &vecs, CR<T> padding);
    static void balance(CR_VEC_LLI differences, VEC2<T> &vecs, CR<T> padding);

  public:
    static VEC_SZ generateSizes(CR_VEC2<T> vecs);
    static size_t getMin(CR_VEC2<T> vecs);
    static size_t getMax(CR_VEC2<T> vecs);
    static VEC_SZ getDifferences(CR_VEC2<T> vecs);
    static VEC_LLI getDifferences(CR_VEC2<T> vecs, CR_LLI targetSz);
    static void balance(VEC2<T> &vecs, CR<T> padding);
    static void balance(VEC2<T> &vecs, CR<T> padding, LLI targetSz);
  };

  //__________________________|
  // VECTOR DUPLICATION TOOLS |
  //__________________________|

  enum VECDUP_ENUM {
    VECDUP_STABLE, VECDUP_UNSTABLE
  };

  template <typename T, VECDUP_ENUM U>
  class VecDupTools final {
  private:
    static bool fillWasted(
      VEC<T> &vec,
      VEC<T> &wasted,
      VecTools<T>::EQUAL_RULE &equalRule,
      CR<T> &a,
      CR<T> &b,
      CR_SZ cutIdx
    );

  public:
    /** Keep only one member of the same */
    static VEC<T> eliminate(
      VEC<T> &vec,
      CR_BOL originalAscending = true,
      // repeated and compared 'T' parameters
      VecTools<T>::EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );

    /** Remove all members that are equal to an external value */
    static VEC<T> clean(
      VEC<T> &vec,
      CR<T> val,
      CR_BOL originalAscending = true,
      // repeated and compared 'T' parameters
      VecTools<T>::EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );
  };
}}

#include "utils/vec-tools.tpp"
#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_HPP__