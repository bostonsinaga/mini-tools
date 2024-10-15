#ifndef __MINI_TOOLS__UTILS__SIZE_TOOLS_H__
#define __MINI_TOOLS__UTILS__SIZE_TOOLS_H__

namespace mini_tools {
namespace utils {

  template <class T>
  class SizeTools {
  private:
    static size_t getMax(VEC_SZ &sizes);
    static VEC_SZ getDifferences(VEC_SZ &sizes);
    static VEC_LLI getDifferences(VEC_SZ &sizes, CR_LLI targetSize);
    static void balance(CR_VEC_SZ differences, VEC2<T> &vecs, CR<T> coveringValue);
    static void balance(CR_VEC_LLI differences, VEC2<T> &vecs, CR<T> coveringValue);

  public:
    static VEC_SZ generateSizes(CR_VEC2<T> vecs);
    static size_t getMax(CR_VEC2<T> vecs);
    static VEC_SZ getDifferences(CR_VEC2<T> vecs);
    static VEC_LLI getDifferences(CR_VEC2<T> vecs, CR_LLI targetSize);
    static void balance(VEC2<T> &vecs, CR<T> coveringValue);
    static void balance(VEC2<T> &vecs, CR<T> coveringValue, LLI targetSize);
  };
}}

#include "size-tools.cpp"
#endif // __MINI_TOOLS__UTILS__SIZE_TOOLS_H__