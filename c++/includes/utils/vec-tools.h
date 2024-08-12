#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_H__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_H__

#include <functional>
#include "../types.h"

namespace mini_tools {
namespace utils {

  template <class T>
  class VecTools {
  public:
    static bool hasIndex(std::vector<T> &vec, int idx);
    static T getAt(std::vector<T> &vec, int idx, T defaultReturn);
    static std::vector<T> getDifferencesToSize(const std::vector<T> &sizes, T targetSize);

    static void concat(
      std::vector<T> &targetVec,
      const std::vector<T> &additionVec
    );

    static std::vector<T> join(
      const std::vector<T> &vecA,
      const std::vector<T> &vecB
    );

    static void cutInterval(
      std::vector<T> &vec,
      std::vector<T> &wasted,
      int begin, int end,
      bool onlyWasted = false,
      bool needDelete = false
    );

    static std::vector<T> cutInterval(
      std::vector<T> &vec,
      int begin, int end,
      bool onlyWasted = false,
      bool needDelete = false
    );

    static void cutSingle(
      std::vector<T> &vec,
      T &wasted,
      int idx,
      bool onlyWasted = false,
      bool needDelete = false
    );

    static T cutSingle(
      std::vector<T> &vec,
      int idx,
      bool onlyWasted = false,
      bool needDelete = false
    );

    /**
     * Set the 'lockedIndex' to true will maintain
     * truncation targeting the initial member
     * (the target index will not point to another member
     * when one of the smaller indexes has finished truncating)
     */
    static void cutIndexes(
      std::vector<T> &vec,
      std::vector<T> &wasted,
      VEC_INT idxs,
      bool lockedIndex = true,
      bool onlyWasted = false,
      bool needDelete = false
    );

    static std::vector<T> cutIndexes(
      std::vector<T> &vec,
      VEC_INT idxs,
      bool lockedIndex = true,
      bool onlyWasted = false,
      bool needDelete = false
    );

    static std::vector<T> cleanDuplicateInside(
      std::vector<T> &vec,
      // repeated and compared 'T' parameters
      std::function<bool(T,T)> equalRule = [](T rep, T com)->bool { return false; }
    );

    static std::vector<T> cleanDuplicateToMember(
      std::vector<T> &vec, T mem,
      // repeated and compared 'T' parameters
      std::function<bool(T,T)> equalRule = [](T rep, T com)->bool { return false; }
    );

    // the 'end' usually 1 index after latest included index
    static void fixIndexInterval(int &begin, int &end, T &vec);
    static bool isIndexIntervalValid(CR_INT begin, CR_INT end, T &vec);
  };
}}

#include "vec-tools.cpp"
#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_H__