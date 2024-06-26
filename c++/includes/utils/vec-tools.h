#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_H__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_H__

#include <functional>
#include "../types.h"

namespace mini_tools {
namespace utils {

  template <class T = int>
  class VecTools {
  public:
    static bool isIndexOf(std::vector<T> &vec, int idx);
    static T getIndexOf(std::vector<T> &vec, int idx, T defaultReturn);
    static VEC_UI getDifferencesToSize(VEC_UI sizes, UI targetSize);

    static void cutInterval(
      std::vector<T> &vec,
      std::vector<T> &wasted,
      int begin, int end,
      bool needDelete = false
    );

    static std::vector<T> cutInterval(
      std::vector<T> &vec,
      int begin, int end,
      bool needDelete = false
    );

    static void cutSingle(
      std::vector<T> &vec,
      T &wasted,
      int idx,
      bool needDelete = false
    );

    static T cutSingle(
      std::vector<T> &vec,
      int idx,
      bool needDelete = false
    );

    static void cutIndexes(
      std::vector<T> &vec,
      std::vector<T> &wasted,
      VEC_INT idxs,
      bool lockedIndex = false,
      bool needDelete = false
    );

    static std::vector<T> cutIndexes(
      std::vector<T> &vec,
      VEC_INT idxs,
      bool lockedIndex = false,
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
  };
}}

#include "vec-tools.cpp"
#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_H__