#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_H__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class VecTools {
  public:
    typedef std::tuple<VEC<T>, VEC<T>> WASTED_TUPLE;
    typedef std::function<bool(CR<T>,CR<T>)> EQUAL_RULE;

  private:
    // invoked in the loop of 'clean..' method
    static bool fillWastedDuplicateInside (
      VEC<T> &vec, EQUAL_RULE &equalRule,
      WASTED_TUPLE &wastedTuple,
      CR<T> &a, CR<T> &b, CR_UI cutIdx
    );

    /**
     * Could be a lambda but better to be
     * a separate method to avoid errors.
     */
    static bool fillWastedDuplicateToMember(
      VEC<T> &vec, WASTED_TUPLE &wastedTuple,
      EQUAL_RULE &equalRule, bool &firstIgnored,
      CR<T> &a, CR<T> &b, CR_UI cutIdx
    );

  public:
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
      CR_BOL validatingIndex = false,
      CR_BOL onlyWasted = false
    );

    static VEC<T> cutInterval(
      VEC<T> &vec,
      CR_INT begin, CR_INT end,
      CR_BOL validatingIndex = false,
      CR_BOL onlyWasted = false
    );

    static void cutSingle(
      VEC<T> &vec,
      T &wasted,
      int idx,
      CR_BOL validatingIndex = false,
      CR_BOL onlyWasted = false
    );

    static T cutSingle(
      VEC<T> &vec,
      CR_INT idx,
      CR_BOL validatingIndex = false,
      CR_BOL onlyWasted = false
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
      CR_BOL validatingIndex = false,
      CR_BOL onlyWasted = false
    );

    static VEC<T> cutIndexes(
      VEC<T> &vec,
      CR_VEC_INT idxs,
      CR_BOL lockedIndex = true,
      CR_BOL validatingIndex = false,
      CR_BOL onlyWasted = false
    );

    /**
     * Compare each member internally.
     * 
     * Returns 2 different values.
     * One based on 'pointer' equality
     * and the other based on value equality.
     */
    static WASTED_TUPLE cleanDuplicateInside(
      VEC<T> &vec,
      CR_BOL originalAscending = true,
      // repeated and compared 'T' parameters
      EQUAL_RULE equalRule = [](CR<T> rep, CR<T> com)->bool { return false; }
    );

    /**
     * Compare all members with an external value
     * or with one of its own members.
     * 
     * Returns the same as 'cleanDuplicateInside'.
     */
    static WASTED_TUPLE cleanDuplicateToMember(
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

#include "data-structures/vec-tools.tpp"
#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_H__