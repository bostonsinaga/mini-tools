#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_H__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class VecTools {
  public:
    typedef std::function<bool(CR<T>,CR<T>)> EQUAL_RULE;

    static bool hasIndex(VEC<T> &vec, CR_INT idx);
    static bool hasIndexes(VEC<T> &vec, CR_VEC_INT idxs);

    // return -1 if not found
    static LLI getIndex(
      VEC<T> &vec,
      CR<T> data,
      // repeated and compared 'T' parameters
      EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );

    static T getAt(
      VEC<T> &vec,
      CR_INT idx,
      CR<T> defaultReturn
    );

    static void concat(
      VEC<T> &targetVec,
      CR_VEC<T> additionVec
    );

    static VEC<T> join(
      CR_VEC<T> vecA,
      CR_VEC<T> vecB
    );

    static void cutInterval(
      VEC<T> &vec,
      VEC<T> &wasted,
      int begin, int end,
      CR_BOL onlyWasted = false,
      CR_BOL validatingIndex = false
    );

    static VEC<T> cutInterval(
      VEC<T> &vec,
      CR_INT begin, CR_INT end,
      CR_BOL onlyWasted = false,
      CR_BOL validatingIndex = false
    );

    static void cutSingle(
      VEC<T> &vec,
      T &wasted,
      int idx,
      CR_BOL onlyWasted = false,
      CR_BOL validatingIndex = false
    );

    static T cutSingle(
      VEC<T> &vec,
      CR_INT idx,
      CR_BOL onlyWasted = false,
      CR_BOL validatingIndex = false
    );

    /**
     * Set the 'lockedIndex' to true will maintain
     * truncation targeting the initial member
     * (the target index will not point to another member
     * when one of the smaller indexes has finished truncating)
     */
    static void cutIndexes(
      VEC<T> &vec,
      VEC<T> &wasted,
      VEC_INT idxs,
      CR_BOL lockedIndex = true,
      CR_BOL onlyWasted = false,
      CR_BOL validatingIndex = false,
      CR_BOL removingExceededIndexes = true
    );

    static VEC<T> cutIndexes(
      VEC<T> &vec,
      CR_VEC_INT idxs,
      CR_BOL lockedIndex = true,
      CR_BOL onlyWasted = false,
      CR_BOL validatingIndex = false,
      CR_BOL removingExceededIndexes = true
    );

    /**
     * Returns 2 different values.
     * One based on 'pointer' equality
     * and the other based on value equality
     */
    static std::tuple<VEC<T>, VEC<T>> cleanDuplicateInside(
      VEC<T> &vec,
      CR_BOL originalAscending = true,
      // repeated and compared 'T' parameters
      EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );

    // Returns the same as 'cleanDuplicateInside'
    static std::tuple<VEC<T>, VEC<T>> cleanDuplicateToMember(
      VEC<T> &vec, CR<T> mem,
      CR_BOL originalAscending = true,
      // repeated and compared 'T' parameters
      EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );

    static void fixIndexes(
      VEC<T> &vec,
      VEC_INT &idxs,
      CR_BOL removed = true
    );

    // range of values ​​from 0 to size - 1
    static void fixIndexInterval(VEC<T> &vec, int &begin, int &end);
    static bool isIndexIntervalValid(VEC<T> &vec, CR_INT begin, CR_INT end);

    // 'T' can also be a vector for multidimensional
    static VEC<T> collapse(CR_VEC2<T> vec);
  };
}}

#include "vec-tools.tpp"
#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_H__