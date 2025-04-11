#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_H__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class VecTools final {
  public:
    typedef std::function<bool(CR<T>,CR<T>)> EQUAL_RULE;

  private:
    VecTools() = delete;

    /** SIZE TOOLS */

    static size_t getMin(VEC_SZ &sizes);
    static size_t getMax(VEC_SZ &sizes);
    static VEC_SZ getDifferences(VEC_SZ &sizes);
    static VEC_LLI getDifferences(VEC_LLI &sizes, CR_LLI targetSize);
    static void balance(CR_VEC_SZ differences, VEC2<T> &vecs, CR<T> coveringValue);
    static void balance(CR_VEC_LLI differences, VEC2<T> &vecs, CR<T> coveringValue);

  public:
    static bool hasIndex(VEC<T> &vec, CR_LLI idx);
    static bool hasIndices(VEC<T> &vec, CR_VEC_LLI indices);

    // return -1 if not found
    static LLI getIndex(
      VEC<T> &vec,
      CR<T> data,
      // repeated and compared 'T' parameters
      EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );

    static T getAt(
      VEC<T> &vec,
      CR_LLI idx,
      CR<T> defaultReturn
    );

    /** VECTORS CONNECTORS */

    /** Connect vector to vector */

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
     * Make sure to use 'fixIndexInterval' or 'isIndexIntervalValid' methods
     * before calling 'erase..' or 'extract..' to prevent undefined behavior
     * when these methods accessing the 'vec' parameter.
     */

    /** STABLE ERASERS (SLOWER) */

    static void eraseSingleStable(
      VEC<T> &vec,
      CR_SZ index,
      T extracted
    );

    static void eraseIntervalStable(
      VEC<T> &vec,
      CR_PAIR<size_t> interval,
      VEC<T> &extracted
    );

    static void eraseIndicesStable(
      VEC<T> &vec,
      CR_VEC<size_t> indices,
      VEC<T> &extracted
    );

    /** UNSTABLE ERASERS (FASTER) */

    static void eraseSingleUnstable(
      VEC<T> &vec,
      CR_SZ index,
      T &extracted
    );

    static void eraseIntervalUnstable(
      VEC<T> &vec,
      CR_PAIR<size_t> interval,
      VEC<T> &extracted
    );

    static void eraseIndicesUnstable(
      VEC<T> &vec,
      CR_VEC<size_t> indices,
      VEC<T> &extracted
    );

    /** STABLE EXTRACTORS */

    static T extractSingleStable(
      VEC<T> &vec,
      CR_SZ index
    );

    static VEC<T> extractIntervalStable(
      VEC<T> &vec,
      CR_PAIR<size_t> interval
    );

    static VEC<T> extractIndicesStable(
      VEC<T> &vec,
      CR_VEC<size_t> indices
    );

    /** UNSTABLE EXTRACTORS */

    static T extractSingleUnstable(
      VEC<T> &vec,
      CR_SZ index
    );

    static VEC<T> extractIntervalUnstable(
      VEC<T> &vec,
      CR_PAIR<size_t> interval
    );

    static VEC<T> extractIndicesUnstable(
      VEC<T> &vec,
      CR_VEC<size_t> indices
    );

    /** INDEX LIMITERS */

    static void fixIndices(
      VEC<T> &vec,
      VEC_LLI &indices,
      CR_BOL needRemove = true
    );

    // range of values ​​from 0 to size - 1
    static void fixIndexInterval(VEC<T> &vec, LLI &begin, LLI &end);
    static bool isIndexIntervalValid(VEC<T> &vec, CR_LLI begin, CR_LLI end);

    /** SIZE TOOLS */

    static VEC_SZ generateSizes(CR_VEC2<T> vecs);
    static size_t getMin(CR_VEC2<T> vecs);
    static size_t getMax(CR_VEC2<T> vecs);
    static VEC_SZ getDifferences(CR_VEC2<T> vecs);
    static VEC_LLI getDifferences(CR_VEC2<T> vecs, CR_LLI targetSize);
    static void balance(VEC2<T> &vecs, CR<T> coveringValue);
    static void balance(VEC2<T> &vecs, CR<T> coveringValue, LLI targetSize);

    /** MEMBER DUPLICATION CLEANERS */

    enum DUPLICATION_ENUM {
      DUPLICATION_STABLE, DUPLICATION_UNSTABLE
    };

    template<DUPLICATION_ENUM U>
    class Duplication final {
    private:
      static bool fillWasted(
        VEC<T> &vec,
        VEC<T> &wasted,
        EQUAL_RULE &equalRule,
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
        EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
      );

      /** Remove all members that are equal to an external value */
      static VEC<T> clean(
        VEC<T> &vec,
        CR<T> val,
        CR_BOL originalAscending = true,
        // repeated and compared 'T' parameters
        EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
      );
    };
  };
}}

#include "utils/vec-tools.tpp"
#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_H__