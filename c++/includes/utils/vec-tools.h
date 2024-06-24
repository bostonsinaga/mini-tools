#ifndef __MINI_TOOLS__UTILS__VEC_TOOLS_H__
#define __MINI_TOOLS__UTILS__VEC_TOOLS_H__

#include <functional>
#include "../types.h"

namespace mini_tools {
namespace utils {

  template <class T = int>
  class VecTools {
  public:
    static bool isIndexOfVector(std::vector<T> *vec, int idx);
    static T getIndexOfVector(std::vector<T> *vec, int idx, T defaultReturn);
    static T cutVector(std::vector<T> *vec, int idx);
    static std::vector<T> cutVector(std::vector<T> *vec, VEC_INT idxs);
    static VEC_UI getDifferencesToSize(VEC_UI sizes, UI targetSize);

    static std::vector<T> cleanDuplicateInsideVector(
      std::vector<T> *vec,
      // repeated and compared 'T' parameters
      std::function<bool(T,T)> equalRule = [](T rep, T com)->bool { return false; }
    );

    static std::vector<T> cleanDuplicateToMember(
      std::vector<T> *vec, T mem,
      // repeated and compared 'T' parameters
      std::function<bool(T,T)> equalRule = [](T rep, T com)->bool { return false; }
    );
  };
}}

#include "vec-tools.cpp"
#endif // __MINI_TOOLS__UTILS__VEC_TOOLS_H__